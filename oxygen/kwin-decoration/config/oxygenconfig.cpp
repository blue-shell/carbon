//////////////////////////////////////////////////////////////////////////////
// config.cpp
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
// Copyright (C) 2008 Lubos Lunak <l.lunak@kde.org>
//
// Based on the Quartz configuration module,
//     Copyright (c) 2001 Karol Szwed <gallium@kde.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "oxygenconfig.h"
#include "oxygenconfig.moc"

#include "../oxygenconfiguration.h"
#include "../oxygenshadowconfiguration.h"

#include <KAboutData>
#include <KAboutApplicationDialog>
#include <KConfigGroup>
#include <KGlobal>
#include <KLocale>

//_______________________________________________________________________
extern "C"
{
  KDE_EXPORT QObject* allocate_config( KConfig* conf, QWidget* parent )
  { return ( new Oxygen::Config( conf, parent ) ); }
}

namespace Oxygen
{

  //_______________________________________________________________________
  Config::Config( KConfig*, QWidget* parent ):
    QObject( parent )
  {

    KGlobal::locale()->insertCatalog("kwin_clients");

    configuration_ = new KConfig( "oxygenrc" );
    KConfigGroup configurationGroup( configuration_, "Windeco");

    userInterface_ = new OxygenConfigurationUI( parent );

    load( configurationGroup );
    connect( userInterface_, SIGNAL(changed()), SLOT( updateChanged() ) );
    userInterface_->show();

  }


  //_______________________________________________________________________
  Config::~Config()
  {
    delete userInterface_;
    delete configuration_;
  }

  //_______________________________________________________________________
  void Config::toggleExpertMode( bool value )
  { userInterface_->toggleExpertMode( value ); }

  //_______________________________________________________________________
  void Config::load( const KConfigGroup& )
  {

    // load standard configuration
    loadConfiguration( OxygenConfiguration( KConfigGroup( configuration_, "Windeco") ) );
    loadShadowConfiguration( QPalette::Active, OxygenShadowConfiguration( QPalette::Active, KConfigGroup( configuration_, "ActiveShadow") ) );
    loadShadowConfiguration( QPalette::Inactive, OxygenShadowConfiguration( QPalette::Inactive, KConfigGroup( configuration_, "InactiveShadow") ) );

    // load exceptions
    OxygenExceptionList exceptions;
    exceptions.read( *configuration_ );
    if( exceptions.empty() )
    { exceptions = OxygenExceptionList::defaultList(); }

    // install in ui
    userInterface_->ui.exceptions->setExceptions( exceptions );
    updateChanged();

  }

  //_______________________________________________________________________
  void Config::updateChanged( void )
  {

    OxygenConfiguration configuration( KConfigGroup( configuration_, "Windeco") );
    bool modified( false );

    if( userInterface_->ui.titleAlignment->currentIndex() != userInterface_->ui.titleAlignment->findText( configuration.titleAlignmentName( true ) ) ) modified = true;
    else if( userInterface_->ui.buttonSize->currentIndex() != userInterface_->ui.buttonSize->findText( configuration.buttonSizeName( true ) ) ) modified = true;
    else if( userInterface_->ui.blendColor->currentIndex() != userInterface_->ui.blendColor->findText( configuration.blendColorName( true ) ) ) modified = true;
    else if( userInterface_->ui.frameBorder->currentIndex() != userInterface_->ui.frameBorder->findText( configuration.frameBorderName( true ) ) ) modified = true;
    else if( userInterface_->ui.sizeGripMode->currentIndex() != userInterface_->ui.sizeGripMode->findText( configuration.sizeGripModeName( true ) ) ) modified = true;
    else if( userInterface_->ui.shadowMode->currentIndex() != userInterface_->ui.shadowMode->findText( configuration.shadowModeName( true ) ) ) modified = true;
    else if( userInterface_->ui.shadowCacheMode->currentIndex() != userInterface_->ui.shadowCacheMode->findText( configuration.shadowCacheModeName( true ) ) ) modified = true;

    else if( userInterface_->ui.drawSeparator->isChecked() != configuration.drawSeparator() ) modified = true;
    else if( userInterface_->ui.titleOutline->isChecked() !=  configuration.drawTitleOutline() ) modified = true;
    else if( userInterface_->shadowConfigurations[0]->isChecked() !=  configuration.useOxygenShadows() ) modified = true;
    else if( userInterface_->shadowConfigurations[1]->isChecked() !=  configuration.useDropShadows() ) modified = true;
    else if( userInterface_->ui.tabsEnabled->isChecked() !=  configuration.tabsEnabled() ) modified = true;
    else if( userInterface_->ui.useAnimations->isChecked() !=  configuration.useAnimations() ) modified = true;
    else if( userInterface_->ui.animateTitleChange->isChecked() !=  configuration.animateTitleChange() ) modified = true;
    else if( userInterface_->ui.narrowButtonSpacing->isChecked() !=  configuration.useNarrowButtonSpacing() ) modified = true;

    // shadow configurations
    else if( shadowConfigurationChanged( OxygenShadowConfiguration( QPalette::Active ), *userInterface_->shadowConfigurations[0] ) ) modified = true;
    else if( shadowConfigurationChanged( OxygenShadowConfiguration( QPalette::Inactive ), *userInterface_->shadowConfigurations[1] ) ) modified = true;

    // exceptions
    else if( exceptionListChanged() ) modified = true;

    // emit relevant signals
    if( modified ) emit changed();
    emit changed( modified );

  }

  //_______________________________________________________________________
  void Config::save( KConfigGroup& )
  {

    // save standard configuration
    KConfigGroup configurationGroup( configuration_, "Windeco");

    // when writing text entries, on needs to make sure that strings written
    // to the configuration file are *not* translated using current locale
    configurationGroup.writeEntry(
      OxygenConfig::TITLE_ALIGNMENT,
      OxygenConfiguration::titleAlignmentName( OxygenConfiguration::titleAlignment( userInterface_->ui.titleAlignment->currentText(), true ), false ) );

    configurationGroup.writeEntry(
      OxygenConfig::BUTTON_SIZE,
      OxygenConfiguration::buttonSizeName( OxygenConfiguration::buttonSize( userInterface_->ui.buttonSize->currentText(), true ), false ) );

    configurationGroup.writeEntry(
      OxygenConfig::BLEND_COLOR,
      OxygenConfiguration::blendColorName( OxygenConfiguration::blendColor( userInterface_->ui.blendColor->currentText(), true ), false ) );

    configurationGroup.writeEntry(
      OxygenConfig::FRAME_BORDER,
      OxygenConfiguration::frameBorderName( OxygenConfiguration::frameBorder( userInterface_->ui.frameBorder->currentText(), true ), false ) );

    configurationGroup.writeEntry(
      OxygenConfig::SIZE_GRIP_MODE,
      OxygenConfiguration::sizeGripModeName( OxygenConfiguration::sizeGripMode( userInterface_->ui.sizeGripMode->currentText(), true ), false ) );

    configurationGroup.writeEntry(
      OxygenConfig::SHADOW_CACHE_MODE,
      OxygenConfiguration::shadowCacheModeName( OxygenConfiguration::shadowCacheMode( userInterface_->ui.shadowCacheMode->currentText(), true ), false ) );

    configurationGroup.writeEntry( OxygenConfig::DRAW_SEPARATOR, userInterface_->ui.drawSeparator->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::DRAW_TITLE_OUTLINE, userInterface_->ui.titleOutline->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::USE_DROP_SHADOWS, userInterface_->shadowConfigurations[1]->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::USE_OXYGEN_SHADOWS, userInterface_->shadowConfigurations[0]->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::TABS_ENABLED, userInterface_->ui.tabsEnabled->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::USE_ANIMATIONS, userInterface_->ui.useAnimations->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::ANIMATE_TITLE_CHANGE, userInterface_->ui.animateTitleChange->isChecked() );
    configurationGroup.writeEntry( OxygenConfig::NARROW_BUTTON_SPACING, userInterface_->ui.narrowButtonSpacing->isChecked() );

    // write exceptions
    userInterface_->ui.exceptions->exceptions().write( *configuration_ );

    // write shadow configuration
    configurationGroup.writeEntry( OxygenConfig::SHADOW_MODE,
        OxygenConfiguration::shadowModeName( OxygenConfiguration::shadowMode( userInterface_->ui.shadowMode->currentText(), true ), false ) );
    saveShadowConfiguration( QPalette::Active, *userInterface_->shadowConfigurations[0] );
    saveShadowConfiguration( QPalette::Inactive, *userInterface_->shadowConfigurations[1] );

    // sync configuration
    configuration_->sync();

  }


  //_______________________________________________________________________
  void Config::saveShadowConfiguration( QPalette::ColorGroup colorGroup, const OxygenShadowConfigurationUI& ui ) const
  {

    assert( colorGroup == QPalette::Active || colorGroup == QPalette::Inactive );

    // save shadow configuration
    KConfigGroup configurationGroup( configuration_, ( (colorGroup == QPalette::Active) ? "ActiveShadow":"InactiveShadow" ) );
    configurationGroup.writeEntry( OxygenConfig::SHADOW_SIZE, ui.ui.shadowSize->value() );
    configurationGroup.writeEntry( OxygenConfig::SHADOW_VOFFSET, 0.1*ui.ui.verticalOffset->value() );
    configurationGroup.writeEntry( OxygenConfig::SHADOW_INNER_COLOR, ui.ui.innerColor->color() );
    configurationGroup.writeEntry( OxygenConfig::SHADOW_OUTER_COLOR, ui.ui.outerColor->color() );
    configurationGroup.writeEntry( OxygenConfig::SHADOW_USE_OUTER_COLOR, ui.ui.useOuterColor->isChecked() );

  }

  //_______________________________________________________________________
  void Config::defaults()
  {

    // install default configuration
    loadConfiguration( OxygenConfiguration() );

    // load shadows
    loadShadowConfiguration( QPalette::Active, OxygenShadowConfiguration( QPalette::Active ) );
    loadShadowConfiguration( QPalette::Inactive, OxygenShadowConfiguration( QPalette::Inactive ) );

    // install default exceptions
    userInterface_->ui.exceptions->setExceptions( OxygenExceptionList::defaultList() );

    updateChanged();

  }

  //_______________________________________________________________________
  void Config::loadConfiguration( const OxygenConfiguration& configuration )
  {

    userInterface_->ui.titleAlignment->setCurrentIndex( userInterface_->ui.titleAlignment->findText( configuration.titleAlignmentName( true ) ) );
    userInterface_->ui.buttonSize->setCurrentIndex( userInterface_->ui.buttonSize->findText( configuration.buttonSizeName( true ) ) );
    userInterface_->ui.blendColor->setCurrentIndex( userInterface_->ui.blendColor->findText( configuration.blendColorName( true ) ) );
    userInterface_->ui.frameBorder->setCurrentIndex( userInterface_->ui.frameBorder->findText( configuration.frameBorderName( true ) ) );
    userInterface_->ui.sizeGripMode->setCurrentIndex( userInterface_->ui.sizeGripMode->findText( configuration.sizeGripModeName( true ) ) );

    userInterface_->ui.drawSeparator->setChecked( configuration.drawSeparator() );
    userInterface_->ui.titleOutline->setChecked( configuration.drawTitleOutline() );
    userInterface_->shadowConfigurations[0]->setChecked( configuration.useOxygenShadows() );
    userInterface_->shadowConfigurations[1]->setChecked( configuration.useDropShadows() );
    userInterface_->ui.tabsEnabled->setChecked( configuration.tabsEnabled() );
    userInterface_->ui.useAnimations->setChecked( configuration.useAnimations() );
    userInterface_->ui.animateTitleChange->setChecked( configuration.animateTitleChange() );
    userInterface_->ui.narrowButtonSpacing->setChecked( configuration.useNarrowButtonSpacing() );
    userInterface_->ui.shadowMode->setCurrentIndex( userInterface_->ui.shadowMode->findText( configuration.shadowModeName( true ) ) );
    userInterface_->ui.shadowCacheMode->setCurrentIndex( userInterface_->ui.shadowCacheMode->findText( configuration.shadowCacheModeName( true ) ) );
  }

  //_______________________________________________________________________
  void Config::loadShadowConfiguration( QPalette::ColorGroup colorGroup, const OxygenShadowConfiguration& configuration )
  {
    assert( colorGroup == QPalette::Active || colorGroup == QPalette::Inactive );
    OxygenShadowConfigurationUI* ui = userInterface_->shadowConfigurations[ (colorGroup == QPalette::Active) ? 0:1 ];
    ui->ui.shadowSize->setValue( configuration.shadowSize() );
    ui->ui.verticalOffset->setValue( 10*configuration.verticalOffset() );
    ui->ui.innerColor->setColor( configuration.innerColor() );
    ui->ui.outerColor->setColor( configuration.outerColor() );
    ui->ui.useOuterColor->setChecked( configuration.useOuterColor() );
  }

  //_______________________________________________________________________
  bool Config::shadowConfigurationChanged( const OxygenShadowConfiguration& configuration, const OxygenShadowConfigurationUI& ui ) const
  {
    bool modified( false );

    if( ui.ui.shadowSize->value() != configuration.shadowSize() ) modified = true;
    else if( 0.1*ui.ui.verticalOffset->value() != configuration.verticalOffset() ) modified = true;
    else if( ui.ui.innerColor->color() != configuration.innerColor() ) modified = true;
    else if( ui.ui.useOuterColor->isChecked() != configuration.useOuterColor() ) modified = true;
    else if( ui.ui.useOuterColor->isChecked() && ui.ui.outerColor->color() != configuration.outerColor() ) modified = true;
    return modified;
  }

  //_______________________________________________________________________
  bool Config::exceptionListChanged( void ) const
  {

    // get saved list
    OxygenExceptionList exceptions;
    exceptions.read( *configuration_ );
    if( exceptions.empty() )
    { exceptions = OxygenExceptionList::defaultList(); }

    // compare to current
    return exceptions != userInterface_->ui.exceptions->exceptions();

  }

}
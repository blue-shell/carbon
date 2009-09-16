//////////////////////////////////////////////////////////////////////////////
// oxygenshadowconfiguration.cpp
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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

#include "oxygenshadowconfiguration.h"

#include <cassert>
#include <kdecoration.h>

namespace Oxygen
{

  //_________________________________________________________
  OxygenShadowConfiguration::OxygenShadowConfiguration( QPalette::ColorGroup colorGroup ):
    colorGroup_( colorGroup ),
    shadowSize_( 25.5 ),
    horizontalOffset_( 0 ),
    useOuterColor_( false )
  {

    // check colorgroup
    assert( colorGroup == QPalette::Active || colorGroup == QPalette::Inactive );

    // vertical offset
    verticalOffset_ = ( OxygenShadowConfiguration::colorGroup() == QPalette::Active ) ? 0:0.2;

    // colors
    innerColor_ = ( OxygenShadowConfiguration::colorGroup() == QPalette::Active ) ?
      KDecoration::options()->color( KDecorationDefines::ColorTitleBar, true ):
      QColor( Qt::black );

    outerColor_ = outerColor2_ = calcOuterColor();
    midColor_ = calcMidColor();

  }

  //_________________________________________________________
  OxygenShadowConfiguration::OxygenShadowConfiguration( QPalette::ColorGroup colorGroup, KConfigGroup group ):
    colorGroup_( colorGroup )
  {

    // get default configuration
    OxygenShadowConfiguration defaultConfiguration( OxygenShadowConfiguration::colorGroup() );

    setShadowSize( group.readEntry( OxygenConfig::SHADOW_SIZE, defaultConfiguration.shadowSize() ) );
    setHorizontalOffset( group.readEntry( OxygenConfig::SHADOW_HOFFSET, defaultConfiguration.horizontalOffset() ) );
    setVerticalOffset( group.readEntry( OxygenConfig::SHADOW_VOFFSET, defaultConfiguration.verticalOffset() ) );
    setInnerColor( group.readEntry( OxygenConfig::SHADOW_INNER_COLOR, defaultConfiguration.innerColor() ) );
    setOuterColor( group.readEntry( OxygenConfig::SHADOW_OUTER_COLOR, defaultConfiguration.outerColor() ) );
    setUseOuterColor( group.readEntry( OxygenConfig::SHADOW_USE_OUTER_COLOR, defaultConfiguration.useOuterColor() ) );
    setOuterColor2( calcOuterColor() );
    setMidColor( calcMidColor() );

  }

  //_________________________________________________________
  bool OxygenShadowConfiguration::operator == ( const OxygenShadowConfiguration& other ) const
  {
    assert( colorGroup() == other.colorGroup() );
    return
      shadowSize() == other.shadowSize() &&
      horizontalOffset() == other.horizontalOffset() &&
      verticalOffset() == other.verticalOffset() &&
      innerColor() == other.innerColor() &&
      outerColor() == other.outerColor() &&
      useOuterColor() == other.useOuterColor();
  }

  //_________________________________________________________
  void OxygenShadowConfiguration::write( KConfigGroup& group ) const
  {
    group.writeEntry( OxygenConfig::SHADOW_SIZE, shadowSize() );
    group.writeEntry( OxygenConfig::SHADOW_HOFFSET, horizontalOffset() );
    group.writeEntry( OxygenConfig::SHADOW_VOFFSET, verticalOffset() );
    group.writeEntry( OxygenConfig::SHADOW_INNER_COLOR, innerColor().name() );
    group.writeEntry( OxygenConfig::SHADOW_OUTER_COLOR, outerColor().name() );
    group.writeEntry( OxygenConfig::SHADOW_USE_OUTER_COLOR, useOuterColor() );
  }

  //_________________________________________________________
  void OxygenShadowConfiguration::setInnerColor( QColor color )
  { innerColor_ = color.isValid() ? color : OxygenShadowConfiguration( colorGroup() ).innerColor(); }

  //_________________________________________________________
  void OxygenShadowConfiguration::setMidColor( QColor color )
  { midColor_ = color.isValid() ? color : OxygenShadowConfiguration( colorGroup() ).midColor(); }

  //_________________________________________________________
  void OxygenShadowConfiguration::setOuterColor( QColor color )
  { outerColor_ = color.isValid() ? color : OxygenShadowConfiguration( colorGroup() ).outerColor(); }

  //_________________________________________________________
  void OxygenShadowConfiguration::setOuterColor2( QColor color )
  { outerColor2_ = color.isValid() ? color : OxygenShadowConfiguration( colorGroup() ).outerColor2(); }

  //_________________________________________________________
  QColor OxygenShadowConfiguration::calcOuterColor( void ) const
  {
    QColor innerColor( OxygenShadowConfiguration::innerColor() );
    assert( innerColor.isValid() );

    // should contain a more ellaborate mathematical formula
    // to calculate outer color from inner color
    return innerColor;
  }

  //_________________________________________________________
  QColor OxygenShadowConfiguration::calcMidColor( void ) const
  {
    QColor innerColor( OxygenShadowConfiguration::innerColor() );
    QColor outerColor( OxygenShadowConfiguration::outerColor() );
    assert( innerColor.isValid() && outerColor.isValid() );

    // should contain a more ellaborate mathematical formula
    // to calculate mid color from inner and outer colors
    return outerColor;
  }

}
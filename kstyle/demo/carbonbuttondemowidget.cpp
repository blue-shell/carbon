//////////////////////////////////////////////////////////////////////////////
// carbonbuttondemowidget.cpp
// carbon buttons demo widget
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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

#include "carbonbuttondemowidget.h"

#include <QMenu>
#include <QIcon>

namespace Carbon
{

    //_____________________________________________________________
    ButtonDemoWidget::ButtonDemoWidget( QWidget* parent ):
        DemoWidget( parent )
    {

        ui.setupUi( this );

        ui.pushButton_3->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.pushButton_4->setIcon( QIcon::fromTheme( QStringLiteral( "carbon") ) );

        installMenu( ui.pushButton_2 );
        installMenu( ui.pushButton_4 );

        _pushButtons
            << ui.pushButton
            << ui.pushButton_2
            << ui.pushButton_3
            << ui.pushButton_4;

        connect( ui.flatButtonCheckBox, SIGNAL(toggled(bool)), SLOT(toggleFlat(bool)) );

        ui.kcombobox_2->addItem( QIcon::fromTheme( QStringLiteral( "carbon" ) ), i18n( "Normal" ) );
        ui.kcombobox_2->addItem( QIcon::fromTheme( QStringLiteral( "document-new" ) ), i18n( "New" ) );
        ui.kcombobox_2->addItem( QIcon::fromTheme( QStringLiteral( "document-open" ) ), i18n( "Open" ) );
        ui.kcombobox_2->addItem( QIcon::fromTheme( QStringLiteral( "document-save" ) ), i18n( "Save" ) );

        ui.toolButton_2->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_2->setIconSize( QSize(16,16 ) );
        ui.toolButton_2->setToolButtonStyle( Qt::ToolButtonTextBesideIcon	);

        ui.toolButton_3->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_4->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_5->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_6->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_7->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        ui.toolButton_8->setIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );

        // add toolbar
        ui.toolBarContainer->setLayout( new QVBoxLayout() );
        _toolBar = new QToolBar( ui.toolBarContainer );
        ui.toolBarContainer->layout()->addWidget( _toolBar );
        _toolBar->addAction( QIcon::fromTheme( QStringLiteral( "document-new" ) ), i18n( "New" ) );
        _toolBar->addAction( QIcon::fromTheme( QStringLiteral( "document-open" ) ), i18n( "Open" ) );
        _toolBar->addAction( QIcon::fromTheme( QStringLiteral( "document-save" ) ), i18n( "Save" ) );
        QAction* action( _toolBar->addAction( QIcon::fromTheme( QStringLiteral( "dialog-password" ) ), i18n( "Toggle authentication" ) ) );
        action->setCheckable( true );
        action->setChecked( true );

        installMenu( ui.toolButton_4 );
        installMenu( ui.toolButton_5 );
        installMenu( ui.toolButton_7 );
        installMenu( ui.toolButton_8 );

        // checkboxes
        ui.checkBox_2->setCheckState( Qt::PartiallyChecked );

        _toolButtons
            << ui.toolButton_3
            << ui.toolButton_4
            << ui.toolButton_5
            << ui.toolButton_6
            << ui.toolButton_7
            << ui.toolButton_8
            << ui.toolButton_9
            << ui.toolButton_10
            << ui.toolButton_11
            << ui.toolButton_12;

        connect( ui.textPosition, SIGNAL(currentIndexChanged(int)), SLOT(textPosition(int)) );
        connect( ui.iconSize, SIGNAL(currentIndexChanged(int)), SLOT(iconSize(int)) );
        ui.iconSize->setCurrentIndex( 2 );
        textPosition(0);
    }

    //_____________________________________________________________
    void ButtonDemoWidget::benchmark( void )
    {
        if( !isVisible() ) return;

        if( true )
        {
            simulator().click( ui.pushButton );

            simulator().selectMenuItem( ui.pushButton_2, 2 );

            simulator().selectComboBoxItem( ui.kcombobox, 0 );
            simulator().selectComboBoxItem( ui.kcombobox, 2 );
            simulator().selectComboBoxItem( ui.kcombobox, 1 );

            simulator().click( ui.toolButton );

            simulator().click( ui.pushButton_3 );

            simulator().selectMenuItem( ui.pushButton_4, 2 );

            simulator().selectComboBoxItem( ui.kcombobox_2, 1 );
            simulator().selectComboBoxItem( ui.kcombobox_2, 2 );
            simulator().selectComboBoxItem( ui.kcombobox_2, 3 );
            simulator().selectComboBoxItem( ui.kcombobox_2, 0 );

            simulator().click( ui.toolButton_2 );
        }

        if( true )
        {
            // toggle flat mode and redo
            simulator().click( ui.flatButtonCheckBox );
            simulator().click( ui.flatButtonCheckBox );
        }

        if( true )
        {
            simulator().click( ui.toolButton_3 );
            simulator().click( ui.toolButton_3 );

            simulator().click( ui.toolButton_6 );
            simulator().click( ui.toolButton_6 );

            simulator().selectMenuItem( ui.toolButton_4, 2 );
            simulator().selectMenuItem( ui.toolButton_7, 2 );

            // TODO select menu item in toolbutton with separated arrow

            foreach( QToolButton* button, _toolBar->findChildren<QToolButton*>() )
            { simulator().click( button ); }

        }

        if( true )
        {

            // change text position
            simulator().selectComboBoxItem( ui.textPosition, 1 );
            simulator().selectComboBoxItem( ui.textPosition, 2 );
            simulator().selectComboBoxItem( ui.textPosition, 3 );
            simulator().selectComboBoxItem( ui.textPosition, 0 );

            // change icon sizes
            simulator().selectComboBoxItem( ui.iconSize, 0 );
            simulator().selectComboBoxItem( ui.iconSize, 1 );
            simulator().selectComboBoxItem( ui.iconSize, 3 );
            simulator().selectComboBoxItem( ui.iconSize, 2 );

        }

        if( true )
        {

            simulator().click( ui.radioButton_2 );
            simulator().click( ui.radioButton_3 );
            simulator().click( ui.radioButton );
        }

        simulator().run();

    }

    //_____________________________________________________________
    void ButtonDemoWidget::toggleFlat( bool value )
    {
        foreach( QPushButton* button, _pushButtons )
        { button->setFlat( value ); }

        ui.toolButton->setAutoRaise( value );
        ui.toolButton_2->setAutoRaise( value );

        ui.kcombobox->setFrame( !value );
        ui.kcombobox_2->setFrame( !value );

    }

    //_____________________________________________________________
    void ButtonDemoWidget::textPosition( int index)
    {
        foreach( QToolButton* button, _toolButtons )
        {
            switch( index )
            {
                default:
                case 0: button->setToolButtonStyle( Qt::ToolButtonIconOnly ); break;
                case 1: button->setToolButtonStyle( Qt::ToolButtonTextOnly ); break;
                case 2: button->setToolButtonStyle( Qt::ToolButtonTextBesideIcon ); break;
                case 3: button->setToolButtonStyle( Qt::ToolButtonTextUnderIcon ); break;
            }
        }

        switch( index )
        {
            default:
            case 0: _toolBar->setToolButtonStyle( Qt::ToolButtonIconOnly ); break;
            case 1: _toolBar->setToolButtonStyle( Qt::ToolButtonTextOnly ); break;
            case 2: _toolBar->setToolButtonStyle( Qt::ToolButtonTextBesideIcon ); break;
            case 3: _toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon ); break;
        }

    }

    //_____________________________________________________________
    void ButtonDemoWidget::iconSize( int index)
    {
        static QList<int> sizes( QList<int>() << 16 << 22 << 32 << 48 );
        foreach( QToolButton* button, _toolButtons )
        { button->setIconSize( QSize( sizes[index], sizes[index] ) ); }

        _toolBar->setIconSize( QSize( sizes[index], sizes[index] ) );

    }


    //_____________________________________________________________
    void ButtonDemoWidget::installMenu( QToolButton* button )
    {
        QMenu* menu = new QMenu();
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-new" ) ), i18n( "New" ) );
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-open" ) ), i18n( "Open" ) );
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-save" ) ), i18n( "Save" ) );
        button->setMenu( menu );
    }

    //_____________________________________________________________
    void ButtonDemoWidget::installMenu( QPushButton* button )
    {
        QMenu* menu = new QMenu();
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-new" ) ), i18n( "New" ) );
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-open" ) ), i18n( "Open" ) );
        menu->addAction( QIcon::fromTheme( QStringLiteral( "document-save" ) ), i18n( "Save" ) );
        button->setMenu( menu );
    }


}
//////////////////////////////////////////////////////////////////////////////
// main.cpp
// carbon-demo main
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

#include "carbondemodialog.h"
#include "../carbon.h"
#include "config-libcarbon.h"

#include <QApplication>

#if QT_VERSION >= 0x050200
#include <QCommandLineOption>
#include <QCommandLineParser>
#endif

#include <QIcon>

#include <KLocalizedString>

namespace Carbon
{

    int run(int argc, char *argv[])
    {
        QApplication app( argc, argv );

        #if QT_VERSION >= 0x050200
        QCommandLineParser commandLine;
        QCommandLineOption enableHighDpi( "highdpi", "Enable High DPI pixmaps" );
        commandLine.addOption( enableHighDpi );
        commandLine.process( app );

        app.setAttribute( Qt::AA_UseHighDpiPixmaps, commandLine.isSet( enableHighDpi ) );
        #endif

        app.setApplicationName( i18n( "Carbon Demo" ) );
        app.setWindowIcon( QIcon::fromTheme( QStringLiteral( "carbon" ) ) );
        DemoDialog dialog;
        dialog.show();
        bool result = app.exec();
        return result;
    }

}

//__________________________________________
int main(int argc, char *argv[])
{
    #if !CARBON_USE_KDE4
    KLocalizedString::setApplicationDomain("carbon_style_demo");
    #endif

    return Carbon::run( argc, argv );

}

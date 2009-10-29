#ifndef oxygensliderengine_h
#define oxygensliderengine_h

//////////////////////////////////////////////////////////////////////////////
// oxygensliderengine.h
// stores event filters and maps widgets to timelines for animations
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

#include "oxygenbaseengine.h"
#include "oxygendatamap.h"
#include "oxygensliderdata.h"

namespace Oxygen
{

    //! stores slider hovered action and timeLine
    class SliderEngine: public BaseEngine
    {

        Q_OBJECT

        public:

        //! constructor
        SliderEngine( QObject* parent ):
        BaseEngine( parent )
        {}

        //! destructor
        virtual ~SliderEngine( void )
        {}

        //! register slider
        virtual bool registerWidget( QWidget* );

        //! true if widget is animated
        virtual bool isAnimated( const QObject* object )
        { return (bool) timeLine( object ); }

        //! animation opacity
        virtual qreal opacity( const QObject* object )
        {
            TimeLine::Pointer timeLine( SliderEngine::timeLine( object ) );
            return timeLine ? timeLine->ratio() : -1;
        }

        //! enability
        virtual void setEnabled( bool value )
        {
            BaseEngine::setEnabled( value );
            data_.setEnabled( value );
        }

        //! duration
        virtual void setDuration( int value )
        {
            BaseEngine::setDuration( value );
            data_.setDuration( value );
        }

        //! max frame
        virtual void setMaxFrame( int value )
        {
            BaseEngine::setMaxFrame( value );
            data_.setMaxFrame( value );
        }

        protected slots:

        //! remove widget from map
        virtual void unregisterWidget( QObject* object )
        { if( object ) data_.remove( object ); }

        protected:

        //! return timeLine associated to action at given position, if any
        virtual TimeLine::Pointer timeLine( const QObject* );

        private:

        //! data map
        DataMap<SliderData> data_;

    };

}

#endif
#ifndef carbonprogressbardata_h
#define carbonprogressbardata_h

//////////////////////////////////////////////////////////////////////////////
// carbonprogressbardata.h
// data container for progressbar animations
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

#include "carbongenericdata.h"
#include <QObject>
#include <QTextStream>

namespace Carbon
{


    //! generic data
    class ProgressBarData: public GenericData
    {

        Q_OBJECT

        public:

        //! constructor
        ProgressBarData( QObject* parent, QWidget* widget, int duration );

        //! destructor
        virtual ~ProgressBarData( void )
        {}

        //! event filter
        virtual bool eventFilter( QObject*, QEvent* );

        //! progressbar value (during animation)
        virtual int value( void ) const
        { return _startValue + opacity()*( _endValue - _startValue ); }

        protected Q_SLOTS:

        //! triggered by progressBar::valueChanged
        void valueChanged( int );

        private:

        //! animation starting value
        int _startValue;

        //! animation ending value
        int _endValue;

    };

}

#endif

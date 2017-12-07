/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_Integer_H
#define Patternist_Integer_H

#include "qschemanumeric_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Implements the value instance of the @c xs:integer type.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_xdm
     * @todo Documentation is missing
     */
    class Integer : public Numeric
    {
    public:

        typedef Numeric::Ptr Ptr;

        /**
         * Constructs an instance from the lexical
         * representation @p strNumeric.
         *
         * @todo Type error handling.
         */
        static AtomicValue::Ptr fromLexical(const QString &strNumeric);

        static Item fromValue(const xsInteger num);

        /**
         * Determines the Effective %Boolean Value of this number.
         *
         * @returns @c false if the number is 0, otherwise @c true.
         */
        bool evaluateEBV(const QExplicitlySharedDataPointer<DynamicContext> &) const;

        virtual QString stringValue() const;

        /**
         * @returns always BuiltinTypes::xsInteger
         */
        virtual ItemType::Ptr type() const;

        virtual xsDouble toDouble() const;
        virtual xsInteger toInteger() const;
        virtual xsFloat toFloat() const;
        virtual xsDecimal toDecimal() const;

        virtual Numeric::Ptr round() const;
        virtual Numeric::Ptr roundHalfToEven(const xsInteger scale) const;
        virtual Numeric::Ptr floor() const;
        virtual Numeric::Ptr ceiling() const;
        virtual Numeric::Ptr abs() const;
        virtual qulonglong toUnsignedInteger() const;

        /**
         * @returns always @c false, @c xs:integer doesn't have
         * not-a-number in its value space.
         */
        virtual bool isNaN() const;

        /**
         * @returns always @c false, @c xs:integer doesn't have
         * infinity in its value space.
         */
        virtual bool isInf() const;
        virtual Item toNegated() const;

        /**
         * @short Returns always @c true.
         */
        virtual bool isSigned() const;
    protected:
        Integer(const xsInteger num);

    private:
        const xsInteger m_value;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif

/*
 * Copyright (C) 2024 Samuel Weinig <sam@webkit.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "CSSPrimitiveNumericTypes+Canonicalization.h"

namespace WebCore {
namespace CSS {

// MARK: Angle

double canonicalizeAngle(double value, AngleUnit unit)
{
    return convertAngle<AngleUnit::Deg>(value, unit);
}

// MARK: Time

double canonicalizeTime(double value, TimeUnit unit)
{
    return convertTime<TimeUnit::S>(value, unit);
}

// MARK: Frequency

double canonicalizeFrequency(double value, FrequencyUnit unit)
{
    return convertFrequency<FrequencyUnit::Hz>(value, unit);
}

// MARK: Resolution

double canonicalizeResolution(double value, ResolutionUnit unit)
{
    return convertResolution<ResolutionUnit::Dppx>(value, unit);
}

} // namespace CSS
} // namespace WebCore

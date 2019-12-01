/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef HQSCALER_H
#define HQSCALER_H

#if defined(USE_HQ2X_SCALER) || defined(USE_HQ3X_SCALER) || defined(USE_HQ4X_SCALER)

#include "Scaler.h"

namespace Pentagram {

class hqScaler : public Scaler {
public:
	hqScaler();

	virtual const uint32    ScaleBits() const;          //< bits for supported integer scaling
	virtual const bool      ScaleArbitrary() const;     //< supports arbitrary scaling of any degree

	virtual const char     *ScalerName() const;         //< Name Of the Scaler (1 word)
	virtual const char     *ScalerDesc() const;         //< Desciption of the Scaler
	virtual const char     *ScalerCopyright() const;    //< Scaler Copyright info

private:
	static bool _Scale16Nat(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                        uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);
	static bool _Scale16Sta(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                        uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);

	static bool _Scale32Nat(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                        uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);
	static bool _Scale32Sta(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                        uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);
	static bool _Scale32_A888(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                          uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);
	static bool _Scale32_888A(Texture *tex, int32 sx, int32 sy, int32 sw, int32 sh,
	                          uint8 *pixel, int32 dw, int32 dh, int32 pitch, bool clamp_src);
};

extern const hqScaler hq_scaler;

};

#endif

#endif

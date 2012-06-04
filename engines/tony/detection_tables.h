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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

namespace Tony {

static const TonyGameDescription gameDescriptions[] = {
	{
		// Tony Tough English
		{
			"tony",
			0,
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 135911071},
				{"roasted.mpc", 0, "57c4a3860cf899443c357e0078ea6f49", 366773},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
	},

	{
		// Tony Tough English Demo
		{
			"tony",
			"Extracted Demo",
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 14972409},
				{"roasted.mpc", 0, "1e247922ec869712bfd96625bc4d3c7c", 39211},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformPC,
			ADGF_DEMO,
			GUIO1(GUIO_NONE)
		},
	},

	{
		// Tony Tough English Demo (Compressed)
		{
			"tony",
			"Demo",
			{
				{"data1.cab", 0, "7d8b6d308f96aee3968ad7910fb11e6d", 58660608},
				AD_LISTEND
			},
			Common::EN_ANY,
			Common::kPlatformPC,
			ADGF_DEMO | GF_COMPRESSED,
			GUIO1(GUIO_NONE)
		},
	},
	{
		// Tony Tough French "Collection Aventure" provided by Strangerke
		{
			"tony",
			0,
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 135911071},
				{"roasted.mpc", 0, "e890c6a41238827bdfa9874a65618b69", 374135},
				AD_LISTEND
			},
			Common::FR_FRA,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
	},
	{
		// Tony Tough German "Shoe Box" provided by Strangerke
		{
			"tony",
			0,
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 135911071},
				{"roasted.mpc", 0, "ccf7ab939a34de1b13df538596431684", 389554},
				AD_LISTEND
			},
			Common::DE_DEU,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
	},
	{
		// Tony Tough Italian provided by Fabio Barzagli
		{
			"tony",
			0,
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 135911071},
				{"roasted.mpc", 0, "1dc896cdb945170d7408598f803411c1", 380001},
				AD_LISTEND
			},
			Common::IT_ITA,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
	},
	{
		// Tony Tough Polish provided by Fabio Barzagli
		{
			"tony",
			0,
			{
				{"roasted.mpr", 0, "06203dbbc85fdd1e6dc8fc211c1a6207", 135911071},
				{"roasted.mpc", 0, "89733ea710669acc8e7900b115f4afef", 389625},
				AD_LISTEND
			},
			Common::PL_POL,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
	},
	{ AD_TABLE_END_MARKER }
};

} // End of namespace Tony

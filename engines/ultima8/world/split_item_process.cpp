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

#include "ultima8/misc/pent_include.h"

#include "split_item_process.h"
#include "ultima8/world/Item.h"
#include "ultima8/graphics/shape_info.h"
#include "ultima8/world/get_object.h"

#include "ultima8/filesys/idata_source.h"
#include "ultima8/filesys/odata_source.h"

// p_dynamic_cast stuff
DEFINE_RUNTIME_CLASSTYPE_CODE(SplitItemProcess, Process);

SplitItemProcess::SplitItemProcess() : Process() {

}

SplitItemProcess::SplitItemProcess(Item *original, Item *target_) {
	assert(original);
	assert(target_);

	assert(original->getShapeInfo()->hasQuantity());
	assert(target_->getShapeInfo()->hasQuantity());

	item_num = original->getObjId();
	target = target_->getObjId();

	// type = TODO
}

void SplitItemProcess::run() {
	Item *original = getItem(item_num);
	Item *targetitem = getItem(target);

	assert(original);
	assert(targetitem);
	assert(original->getShapeInfo()->hasQuantity());
	assert(targetitem->getShapeInfo()->hasQuantity());

	uint16 movecount = static_cast<uint16>(result);

	assert(movecount <= original->getQuality());

	uint16 origcount = original->getQuality() - movecount;
	uint16 targetcount = targetitem->getQuality() + movecount;

	pout << "SplitItemProcess splitting: " << movecount << ": "
	     << origcount << "-" << targetcount << std::endl;

	if (targetcount > 0) {
		targetitem->setQuality(targetcount);
		targetitem->callUsecodeEvent_combine();
	} else {
		targetitem->destroy();
		targetitem = 0;
	}

	if (origcount > 0) {
		original->setQuality(origcount);
		original->callUsecodeEvent_combine();
	} else {
		original->destroy(); // note: this terminates us
		original = 0;
	}

	result = 0;

	if (!is_terminated())
		terminate();
}

void SplitItemProcess::saveData(ODataSource *ods) {
	Process::saveData(ods);

	ods->write2(target);
}

bool SplitItemProcess::loadData(IDataSource *ids, uint32 version) {
	if (!Process::loadData(ids, version)) return false;

	target = ids->read2();

	return true;
}

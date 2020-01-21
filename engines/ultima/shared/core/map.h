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

#ifndef ULTIMA_SHARED_CORE_MAP_H
#define ULTIMA_SHARED_CORE_MAP_H

#include "common/array.h"
#include "common/ptr.h"
#include "ultima/shared/core/rect.h"
#include "ultima/shared/gfx/dungeon_surface.h"

namespace Ultima {
namespace Shared {

enum Direction {
	DIR_LEFT = 1, DIR_RIGHT = 2, DIR_UP = 3, DIR_DOWN = 4
};

typedef byte MapCell;

class Game;
class Map;

/**
 * Base class for things that appear within a map, such as monsters, transports, or people
 */
class MapWidget {
protected:
	Game *_game;						// Game reference
	Map *_map;							// Map reference
public:
	Point _position;					// Position within the map
	Common::String _name;				// Name of widget
public:
	/**
	 * Constructor
	 */
	MapWidget(Game *game, Map *map) : _game(game), _map(map) {}
	MapWidget(Game *game, Map *map, const Point &pt) : _game(game), _map(map), _position(pt) {}
	MapWidget(Game *game, Map *map, const Point &pt, const Common::String &name) :
		_game(game), _map(map), _position(pt), _name(name) {}

	/**
	 * Destructor
	 */
	virtual ~MapWidget() {}

	/**
	 * Get the tile for the widget
	 */
	virtual uint getTileNum() const { return 0; }

	/**
	 * Returns true if the player can move onto a tile the widget occupies
	 */
	virtual bool isBlocking() const { return false; }
};

typedef Common::SharedPtr<MapWidget> MapWidgetPtr;

/**
<<<<<<< HEAD
 * Base class for items that appear within the dungeons
 */
class MapItem {
protected:
	Game *_game;						// Game reference
	Map *_map;							// Map reference
public:
	Point _position;					// Position within the map
public:
	/**
	* Constructor
	*/
	MapItem(Game *game, Map *map) : _game(game), _map(map) {}

	/**
 	 * Destructor
	 */
	virtual ~MapItem() {}

	/**
	 * Draw the item
	 */
	virtual void draw(Shared::DungeonSurface &s, uint distance) {}
};

typedef Common::SharedPtr<MapItem> MapItemPtr;

/**
=======
>>>>>>> 04ee1c8... ULTIMA1: Merging map _items array into _widgets
 * Contains data about a given position within the map
 */
class MapTile {
public:
	int _tileId;							// Tile Id
	int _tileNum;							// Tile number to display. Normally equals Tile Id, but can differ in rare cases
	int _widgetNum;							// Widget number, if any
	MapWidget *_widget;						// Widget pointer
	int _itemNum;							// Item number, if any
	// Dungeon tile flags 
	bool _isDoor, _isSecretDoor;
	bool _isLadderUp, _isLadderDown;
	bool _isWall, _isHallway, _isBeams;
public:
	/**
	 * Constructor
	 */
	MapTile() : _tileNum(-1), _tileId(-1), _widgetNum(-1), _widget(nullptr), _itemNum(-1),
	_isDoor(false), _isSecretDoor(false), _isLadderUp(false), _isLadderDown(false), _isWall(false),
		_isHallway(false), _isBeams(false) {}

	/**
 	 * Destructor
	 */
	virtual ~MapTile() {}

	/**
	 * Clears the map tile information
	 */
	virtual void clear();

	/**
	 * Returns true if the tile is a door in a dungeon
	 */
	bool isDoor() const { return _isDoor; }

	/**
	 * Returns true if the tile is a wall or secret door in a dungeon
	 */
	bool isWallOrSecretDoor() const { return _isWall || _isSecretDoor; }

	/**
	 * Returns true if the tile in a dungeon is a type that has walls on it: walls, doors, or secret doors
	 */
	bool isWallOrDoorway() const { return _isWall || _isDoor || _isSecretDoor; }

	/**
	 * Returns true if a tile is a solid type within a dungeon
	 */
	bool isSolid() const { return !(_isHallway || _isLadderUp || _isLadderDown || _isBeams); }
};

/**
 * Base class for managing maps within the game
 */
class Map {
	/**
	 * Stores state about the current viewport being displayed. It's kept as part of the Map class
	 * as a convenience to be alongside the current party position
	 */
	struct ViewportPosition {
		Point _topLeft;					// Top, left tile position for viewport
		Point _size;					// Size of the viewport. Just in case we ever allow it to change
		int _mapId;						// Maze the viewport is for. Used to detect when the map changes

		/**
		 * Constructor
		 */
		ViewportPosition() : _topLeft(-1, -1), _mapId(-1) {}

		/**
		 * Returns true if the viewport is in a valid state
		 */
		bool isValid() const { return _mapId != -1; }

		/**
		 * Resets the viewport position, so it'll get recalculated the next call to getViewportPosition
		 */
		void reset() { _mapId = -1; }
	};

	/**
	 * Internal class used for storing the data for a row
	 */
	struct MapCellsRow {
		friend class Map;
	private:
		Common::Array<MapCell> _data;
	public:
		byte &operator[](int idx) { return _data[idx]; }
		byte operator[](int idx) const { return _data[idx]; }
	};
protected:
	byte _mapId;						// The map Id
	Common::Array<MapWidgetPtr> _widgets;	// Party, monsteres, transports, etc.
	Common::Array<MapCellsRow> _data;	// Data for the map
	Point _position;					// Current position within the map
	ViewportPosition _viewportPos;		// Viewport position
protected:
	/**
	 * Set the size of the map
	 */
	void setDimensions(const Point &size);
public:
	Point _size;						// X, Y size of the map
	Point _tilesPerOrigTile;			// For enhanced modes, number of tiles per original game tile
	Direction _direction;				// Current direction being faced in the underworld
	bool _fixed;						// Town/city type maps that don't scroll as the player moves
	uint _dungeonLevel;					// Dungeon level number
public:
	/**
	 * Constructor
	 */
	Map();
	virtual ~Map() {}

	/**
	 * Clears all map data
	 */
	virtual void clear();

	/**
	 * Returns the width of the map
	 */
	size_t width() const { return _size.x; }

	/**
	 * Returns the height of the map
	 */
	size_t height() const { return _size.y; }

	/**
	 * Return the current position
	 */
	Point getPosition() const { return _position; }

	/**
	 * Returns a delta for the cell in front of the player based on the direction they're facing
	 */
	Point getDirectionDelta() const;

	/**
	 * Gets a point relative to the current position
	 */
	Point getDeltaPosition(const Point &delta);

	/**
	 * Set the position
	 */
	void setPosition(const Point &pt);

	/**
	 * Get the viewport position
	 */
	Point getViewportPosition(const Point &viewportSize);

	/**
	 * Shifts the viewport by a given delta
	 */
	void shiftViewport(const Point &delta);

	/**
	 * Adds a widget to the map
	 */
	void addWidget(MapWidget *widget);

	/**
	 * Gets a tile at a given position
	 */
	virtual void getTileAt(const Point &pt, MapTile *tile);

	/**
	 * Load a given map
	 */
	virtual void loadMap(int mapId);
};

} // End of namespace Shared
} // End of namespace Ultima

#endif

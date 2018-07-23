
#include <tileset/observer.h>
namespace tcod {
TilesetSubject::~TilesetSubject(void) {
  for (std::weak_ptr<TilesetObserver> weak_observer : observer_pointers_) {
    if (auto observer = weak_observer.lock()) {
      observer->OnTilesetDetach();
    }
  }
}
void TilesetSubject::AttachTilesetObserver(
    std::weak_ptr<TilesetObserver> observer,
    const Tileset &tileset,
    const std::vector<Tile>& tiles) {
  observer_pointers_.push_back(observer);
  observer.lock()->OnTilesetAttach(tileset, tiles);
}
void TilesetSubject::NotifyChanged(const Tileset &tileset,
                                   const std::vector<Tile>& tiles,
                                   const IdTileRefPairVector_ &changes) {
  for (std::weak_ptr<TilesetObserver> weak_observer : observer_pointers_) {
    if (auto observer = weak_observer.lock()) {
      observer->OnTilesetChanged(tileset, tiles, changes);
    }
  }
}
} // namespace tcod
#include <iostream>
#include "Player.h"
#include "Tile.h"
using namespace std;

int main()
{
    Player test("Cat", 7);

    cout << "Hand size: " << test.getHandTiles().size() << endl;

    Tile one('C', 3);
    Tile two('A', 1);
    Tile three('T', 3);
    Tile four('?', 0);
    Tile five('M', 2);

    vector<Tile*> tile_list; 

    tile_list.push_back(&one);
    tile_list.push_back(&two);
    tile_list.push_back(&three);
    tile_list.push_back(&four);
    tile_list.push_back(&five);

    test.addTiles(tile_list);

    cout << "Hand size: " << test.getHandTiles().size() << endl;

    cout << test.hasTiles("CAT?S", false) << endl;

    set<Tile*> playerhand = test.getHandTiles();

    for(set<Tile*>::iterator it = playerhand.begin(); it != playerhand.end(); ++it)
        { 
            cout << (*it)->getLetter() << endl;
        }

    test.takeTiles("ATM", true);
    cout << "Hand size: " << test.getHandTiles().size() << endl;
    playerhand = test.getHandTiles();
    for(set<Tile*>::iterator it = playerhand.begin(); it != playerhand.end(); ++it)
    { 
        cout << (*it)->getLetter() << endl;
    }
    //cout << test.getMaxTiles() << endl;

    return 0;
}
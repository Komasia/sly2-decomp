/* class: episodes (func_001DDDB8: the current episode's name): the text id of episode iepisode's name (0x6D + iepisode
 * for the 9 episodes 0..8), -1 otherwise. */
int func_001DDD40(int iepisode)
{
    int id = -1;
    switch (iepisode) {
    case 0: id = 0x6D; break;
    case 1: id = 0x6E; break;
    case 2: id = 0x6F; break;
    case 3: id = 0x70; break;
    case 4: id = 0x71; break;
    case 5: id = 0x72; break;
    case 6: id = 0x73; break;
    case 7: id = 0x74; break;
    case 8: id = 0x75; break;
    }
    return id;
}

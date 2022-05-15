#include <math.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class monster {
 public:
  int id;
  int type;
  int x;
  int y;
  int shield_life;
  int is_controlled;
  int health;
  int vx;
  int vy;
  int near_base;
  int threat_for;
  monster(int id_, int x_, int y_, int shield_life_, int is_controlled_,
          int health_, int vx_, int vy_, int near_base_, int threat_for_) {
    id = id_;
    x = x_;
    y = y_;
    shield_life = shield_life_;
    is_controlled = is_controlled_;
    health = health_;
    vx = vx_;
    vy = vy_;
    near_base = near_base_;
    threat_for = threat_for_;
  }
};
class hero {
 public:
  int id;
  int type;
  int x;
  int y;
  int shield_life;
  int is_controlled;
  int health;
  int vx;
  int vy;
  int near_base;
  int threat_for;
  hero(int id_, int x_, int y_, int shield_life_, int is_controlled_,
       int health_, int vx_, int vy_, int near_base_, int threat_for_) {
    id = id_;
    x = x_;
    y = y_;
    shield_life = shield_life_;
    is_controlled = is_controlled_;
    health = health_;
    vx = vx_;
    vy = vy_;
    near_base = near_base_;
    threat_for = threat_for_;
  }
  hero() {}
};
std::vector<monster *> monsterarray;
hero firstHero;
hero secondHero;
hero thirdHero;
int wave = 1;
int enemybase_x, enemybase_y;
monster *firstHeroMonster = NULL;
monster *secondHeroMonster = NULL;
monster *thirdHeroMonster = NULL;
std::vector<hero *> enemyarray;
hero *closestBaseEnemy;
hero *closestEnemyBase;
double norm(int x, int y) {
  if (x == 0 && y == 0) {
    return 1;
  }
  return sqrt(x * x + y * y);
}
monster *findById(int id) {
  for (auto i : monsterarray) {
    if (i->id == id) {
      return i;
    }
  }
  return NULL;
}
double dist(int x, int y, int a, int l) {
  return std::sqrt((x - a) * (x - a) + (y - l) * (y - l));
}
hero *closestEnemyHero(int x, int y) {
  hero *e;
  double distan = 1000000;
  for (auto i : enemyarray) {
    if (dist(x, y, i->x, i->y)) {
      distan = dist(x, y, i->x, i->y);
      e = i;
    }
  }
  return e;
}
int base_x;  // The corner of the map representing your base
int base_y;
bool moved = false;
monster *closestMonsterToHero(int hero) {
  double distan = 1000000;
  double enemybasedistan = 1000000;
  monster *m = NULL;
  for (auto i : monsterarray) {
    if (hero == 1) {
      if (wave <= 2) {
        if (dist(firstHero.x, firstHero.y, i->x, i->y) < distan &&
            i->is_controlled == false &&
            ((enemybase_x - i->x) /
                         norm(enemybase_x - i->x, enemybase_y - i->y) -
                     i->vx / norm(i->vx, i->vy) >
                 0.01 ||
             (enemybase_y - i->y) /
                         norm(enemybase_x - i->x, enemybase_y - i->y) -
                     i->vy / norm(i->vx, i->vy) >
                 0.01)) {
          cerr << "vec " << (enemybase_x - i->x) << " " << (enemybase_y - i->y)
               << " " << i->vx << " " << i->vy << endl;
          distan = dist(firstHero.x, firstHero.y, i->x, i->y);
          m = i;
        }
      } else if (wave == 3) {
        if (closestBaseEnemy == NULL ||
            dist(closestBaseEnemy->x, closestBaseEnemy->y, base_x, base_y) <
                8000) {
          if (dist(base_x, base_y, i->x, i->y) < distan) {
            distan = dist(base_x, base_y, i->x, i->y);
            m = i;
          }
        } else {
          if (dist(firstHero.x, firstHero.y, i->x, i->y) < distan &&
              i->is_controlled == false &&
              ((enemybase_x - i->x) /
                           norm(enemybase_x - i->x, enemybase_y - i->y) -
                       i->vx / norm(i->vx, i->vy) >
                   0.01 ||
               (enemybase_y - i->y) /
                           norm(enemybase_x - i->x, enemybase_y - i->y) -
                       i->vy / norm(i->vx, i->vy) >
                   0.01)) {
            cerr << "vec " << (enemybase_x - i->x) << " "
                 << (enemybase_y - i->y) << " " << i->vx << " " << i->vy
                 << endl;
            distan = dist(firstHero.x, firstHero.y, i->x, i->y);
            m = i;
          }
        }
      }
    } else if (hero == 2) {
      if (wave <= 2) {
        if (dist(secondHero.x, secondHero.y, i->x, i->y) < distan &&
            dist(base_x, base_y, i->x, i->y) > 5000 &&
            i->is_controlled == false &&
            ((enemybase_x - i->x) /
                         norm(enemybase_x - i->x, enemybase_y - i->y) -
                     i->vx / norm(i->vx, i->vy) >
                 0.01 ||
             (enemybase_y - i->y) /
                         norm(enemybase_x - i->x, enemybase_y - i->y) -
                     i->vy / norm(i->vx, i->vy) >
                 0.01)) {
          distan = dist(secondHero.x, secondHero.y, i->x, i->y);
          m = i;
        }
      } else if (wave == 3) {
        if (dist(enemybase_x, enemybase_y, i->x, i->y) < enemybasedistan &&
            dist(enemybase_x, enemybase_y, i->x, i->y) < 5000) {
          enemybasedistan = dist(enemybase_x, enemybase_y, i->x, i->y);
          m = i;
        }
      }
    } else if (hero == 3) {
      if (dist(base_x, base_y, i->x, i->y) < distan) {
        distan = dist(base_x, base_y, i->x, i->y);
        m = i;
      }
    }
  }
  if (m == NULL) {
    for (auto i : monsterarray) {
      if (hero == 2) {
        if (wave == 3) {
          if (dist(enemybase_x, enemybase_y, i->x, i->y) < 10000) {
            distan = dist(secondHero.x, secondHero.y, i->x, i->y);
            m = i;
          }
        }
      }
    }
  }
  return m;
}

int main() {
  cin >> base_x >> base_y;
  cin.ignore();
  int heroes_per_player;  // Always 3
  cin >> heroes_per_player;
  cin.ignore();
  int countHero = 0;
  if (base_x == 0) {
    enemybase_x = 17630;
    enemybase_y = 9000;
  } else {
    enemybase_x = 0;
    enemybase_y = 0;
  }

  // game loop
  while (1) {
    if (countHero == 3) {
      countHero = 0;
    }
    countHero++;
    int health;  // Each player's base health
    int mana;    // Ignore in the first league; Spend ten mana to cast a spell
    int enemyhealth;
    int enemymana;
    cin >> health >> mana;
    cin.ignore();
    cin >> enemyhealth >> enemymana;
    cin.ignore();
    int entity_count;  // Amount of heros and monsters you can see
    cin >> entity_count;
    cin.ignore();
    for (int i = 0; i < entity_count; i++) {
      int id;    // Unique identifier
      int type;  // 0=monster, 1=your hero, 2=opponent hero
      int x;     // Position of this entity
      int y;
      int shield_life;  // Ignore for this league; Count down until shield spell
                        // fades
      int is_controlled;  // Ignore for this league; Equals 1 when this entity
                          // is under a control spell
      int health;         // Remaining health of this monster
      int vx;             // Trajectory of this monster
      int vy;
      int near_base;   // 0=monster with no target yet, 1=monster targeting a
                       // base
      int threat_for;  // Given this monster's trajectory, is it a threat to
                       // 1=your base, 2=your opponent's base, 0=neither
      cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >>
          vx >> vy >> near_base >> threat_for;
      cin.ignore();
      if (type == 0) {
        monsterarray.push_back(new monster(id, x, y, shield_life, is_controlled,
                                           health, vx, vy, near_base,
                                           threat_for));
      } else if (type == 1) {
        if (id % 3 == 0) {
          firstHero = hero(id, x, y, shield_life, is_controlled, health, vx, vy,
                           near_base, threat_for);
        } else if (id % 3 == 1) {
          secondHero = hero(id, x, y, shield_life, is_controlled, health, vx,
                            vy, near_base, threat_for);
        } else {
          thirdHero = hero(id, x, y, shield_life, is_controlled, health, vx, vy,
                           near_base, threat_for);
        }
      } else if (type == 2) {
        enemyarray.push_back(new hero(id, x, y, shield_life, is_controlled,
                                      health, vx, vy, near_base, threat_for));
      }
    }
    cerr << "length " << monsterarray.size() << endl;
    if (monsterarray.size() > 0) {
      firstHeroMonster = closestMonsterToHero(1);
      cerr << "firs" << endl;
      secondHeroMonster = closestMonsterToHero(2);
      cerr << "seco" << endl;
      thirdHeroMonster = closestMonsterToHero(3);
      cerr << "thir" << endl;
      if (firstHeroMonster == NULL) {
        cerr << "monster" << endl;
      }
      closestBaseEnemy = closestEnemyHero(base_x, base_y);

      // Write an action using cout. DON'T FORGET THE "<< endl"
      // To debug: cerr << "Debug messages..." << endl;

      // In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL
      // <spellParams>;
      if (firstHeroMonster != NULL) {
        cerr << wave << endl;
        if (firstHeroMonster->health > 12) {
          if (wave < 2) {
            wave = 2;
          }
        }
        if (firstHeroMonster->health > 17) {
          if (wave < 3) {
            wave = 3;
          }
        }
        if (dist(firstHero.x, firstHero.y, base_x, base_y) > 8000) {
          cout << "MOVE " << base_x << " " << base_y << " 1" << endl;
        } else if (closestBaseEnemy != NULL &&
                   dist(firstHero.x, firstHero.y, closestBaseEnemy->x,
                        closestBaseEnemy->y) < 2200 &&
                   dist(closestBaseEnemy->x, closestBaseEnemy->y, base_x,
                        base_y) < 4000 &&
                   closestBaseEnemy->shield_life == 0 && mana > 20 &&
                   wave >= 2) {
          cout << "SPELL CONTROL " << closestBaseEnemy->id << " " << enemybase_x
               << " " << enemybase_y << " 1" << endl;
        } else if (closestBaseEnemy != NULL &&
                   dist(firstHero.x, firstHero.y, closestBaseEnemy->x,
                        closestBaseEnemy->y) < 1280 &&
                   dist(closestBaseEnemy->x, closestBaseEnemy->y, base_x,
                        base_y) < 5000 &&
                   closestBaseEnemy->shield_life == 0 && mana > 20 &&
                   wave >= 2) {
          cout << "SPELL WIND "
               << " " << enemybase_x << " " << enemybase_y << " 1" << endl;
        } else if (dist(closestBaseEnemy->x, closestBaseEnemy->y, base_x,
                        base_y) < 5000 &&
                   dist(firstHero.x, firstHero.y, closestBaseEnemy->x,
                        closestBaseEnemy->y) > 2200) {
          cout << "MOVE " << closestBaseEnemy->x << " " << closestBaseEnemy->y
               << " 1" << endl;
        } else if (dist(firstHeroMonster->x, firstHeroMonster->y, base_x,
                        base_y) < 2500 &&
                   dist(firstHero.x, firstHero.y, firstHeroMonster->x,
                        firstHeroMonster->y) < 1280 &&
                   firstHeroMonster->shield_life == 0 && mana > 10) {
          cout << "SPELL WIND " << enemybase_x << " " << enemybase_y << " 1"
               << endl;
        } else if (dist(firstHero.x, firstHero.y, firstHeroMonster->x,
                        firstHeroMonster->y) < 2200 &&
                   dist(firstHeroMonster->x, firstHeroMonster->y, base_x,
                        base_y) < 5000 &&
                   wave == 3 &&
                   (enemybase_x - firstHeroMonster->x) /
                           (enemybase_y - firstHeroMonster->y) !=
                       firstHeroMonster->vx / firstHeroMonster->vy &&
                   mana > 60) {
          cerr << "control " << firstHeroMonster->x << " "
               << firstHeroMonster->y << endl;
          cout << "SPELL CONTROL " << firstHeroMonster->id << " " << enemybase_x
               << " " << enemybase_y << endl;
        } else {
          cout << "MOVE " << firstHeroMonster->x << " " << firstHeroMonster->y
               << " 1" << endl;
        }
      } else {
        if (base_x == 0) {
          cout << "MOVE " << 8000 << " " << 2000 << " 1" << endl;
        } else {
          cout << "MOVE " << 9630 << " " << 7000 << " 1" << endl;
        }
      }
      if (dist(secondHero.x, secondHero.y, enemybase_x, enemybase_y) > 10000) {
        cout << "MOVE " << enemybase_x << " " << enemybase_y << " 2" << endl;
      } else if (dist(secondHero.x, secondHero.y, enemybase_x, enemybase_y) <
                 2000) {
        cout << "MOVE " << base_x << " " << base_y << " 2" << endl;
      } else {
        if (secondHeroMonster != NULL) {
          if (secondHeroMonster->health > 12) {
            if (wave < 2) {
              wave = 2;
            }
          }
          if (secondHeroMonster->health > 17) {
            if (wave < 3) {
              wave = 3;
            }
          }
          if (wave == 3) {
            closestEnemyBase = closestEnemyHero(secondHero.x, secondHero.y);
            if (closestEnemyBase != NULL) {
              cerr << "shield "
                   << dist(secondHero.x, secondHero.y, closestEnemyBase->x,
                           closestEnemyBase->y)
                   << " " << closestEnemyBase->x << " " << closestEnemyBase->y
                   << endl;
            }
            if (closestEnemyBase != NULL &&
                dist(secondHero.x, secondHero.y, closestEnemyBase->x,
                     closestEnemyBase->y) < 2200 &&
                secondHero.shield_life == 0 && mana > 20) {
              cout << "SPELL SHIELD " << secondHero.id << " 2" << endl;
            } else {
              if (dist(secondHero.x, secondHero.y, enemybase_x, enemybase_y) >
                  10000) {
                cout << "MOVE " << enemybase_x << " " << enemybase_y << " 2"
                     << endl;
              } else {
                if (moved == true) {
                  cout << "MOVE " << enemybase_x << " " << enemybase_y << " 2"
                       << endl;
                  moved = false;
                } else {
                  if (mana <= 20) {
                    cout << "MOVE " << secondHeroMonster->x << " "
                         << secondHeroMonster->y << " 2" << endl;
                  } else {
                    if (dist(secondHero.x, secondHero.y, secondHeroMonster->x,
                             secondHeroMonster->y) < 2200 &&
                        dist(secondHero.x, secondHero.y, enemybase_x,
                             enemybase_y) < 12000 &&
                        mana > 20 && secondHeroMonster->shield_life == 0) {
                      if (dist(secondHeroMonster->x, secondHeroMonster->y,
                               enemybase_x, enemybase_y) < 5000) {
                        cout << "SPELL SHIELD " << secondHeroMonster->id << " 2"
                             << endl;
                      } else if (dist(secondHeroMonster->x,
                                      secondHeroMonster->y, enemybase_x,
                                      enemybase_y) > 8000 &&
                                 ((enemybase_x - secondHeroMonster->x) /
                                              norm(enemybase_x -
                                                       secondHeroMonster->x,
                                                   enemybase_y -
                                                       secondHeroMonster->y) -
                                          secondHeroMonster->vx /
                                              norm(secondHeroMonster->vx,
                                                   secondHeroMonster->vy) >
                                      0.01 ||
                                  (enemybase_y - secondHeroMonster->y) /
                                              norm(enemybase_x -
                                                       secondHeroMonster->x,
                                                   enemybase_y -
                                                       secondHeroMonster->y) -
                                          secondHeroMonster->vy /
                                              norm(secondHeroMonster->vx,
                                                   secondHeroMonster->vy) >
                                      0.01) &&
                                 secondHeroMonster->is_controlled == false) {
                        cout << "SPELL CONTROL " << secondHeroMonster->id << " "
                             << enemybase_x << " " << enemybase_y << " 2"
                             << endl;
                      } else if (dist(secondHero.x, secondHero.y,
                                      secondHeroMonster->x,
                                      secondHeroMonster->y) < 1280) {
                        moved = true;
                        cout << "SPELL WIND " << enemybase_x << " "
                             << enemybase_y << " 2" << endl;
                      } else {
                        if (base_x == 0) {
                          cout << "MOVE " << 12000 << " " << 6000 << " 2"
                               << endl;
                        } else {
                          cout << "MOVE " << 5630 << " " << 3000 << " 2"
                               << endl;
                        }
                      }
                    } else {
                      if (base_x == 0) {
                        cout << "MOVE " << 8000 << " " << 2000 << " 2" << endl;
                      } else {
                        cout << "MOVE " << 9630 << " " << 7000 << " 2" << endl;
                      }
                    }
                  }
                }
                /*if (dist(secondHero.x, secondHero.y, secondHeroMonster->x,
                         secondHeroMonster->y) < 2200 &&
                    mana > 20 && secondHeroMonster->is_controlled == false &&
                    secondHeroMonster->shield_life == 0) {
                  cerr << "enemye "
                       << dist(secondHero.x, secondHero.y, enemybase_x,
                enemybase_y)
                       << endl;
                  if (dist(secondHero.x, secondHero.y, enemybase_x, enemybase_y)
                < 10000 && dist(secondHero.x, secondHero.y, enemybase_x,
                enemybase_y) > 8000) { cout << "SPELL CONTROL " <<
                secondHeroMonster->id << " "
                         << enemybase_x << " " << enemybase_y << " 2" << endl;
                  } else if (((enemybase_x - secondHeroMonster->x) /
                                          norm(enemybase_x -
                secondHeroMonster->x, enemybase_y - secondHeroMonster->y)
                - secondHeroMonster->vx / norm(secondHeroMonster->vx,
                                               secondHeroMonster->vy) <
                                  0.01 &&
                              (enemybase_y - secondHeroMonster->y) /
                                          norm(enemybase_x -
                secondHeroMonster->x, enemybase_y - secondHeroMonster->y)
                - secondHeroMonster->vy / norm(secondHeroMonster->vx,
                                               secondHeroMonster->vy) <
                                  0.01) &&
                             dist(secondHeroMonster->x, secondHeroMonster->y,
                                  enemybase_x, enemybase_y) > 4000) {
                    cout << "SPELL SHIELD " << secondHeroMonster->id << " 2"
                         << endl;
                  } else if (dist(secondHero.x, secondHero.y, enemybase_x,
                                  enemybase_y) < 4000 &&
                             dist(secondHero.x, secondHero.y,
                secondHeroMonster->x, secondHeroMonster->y) < 1280) { moved =
                true; cout << "SPELL WIND " << enemybase_x << " " << enemybase_y
                         << " 2" << endl;
                  } else {
                    if (base_x == 0) {
                      cout << "MOVE " << 10000 << " " << 8000 << endl;
                    } else {
                      cout << "MOVE " << 6000 << " " << 2000 << endl;
                    }
                  }
                } else if (((enemybase_x - secondHeroMonster->x)
                                        norm(enemybase_x - secondHeroMonster->x,
                                             enemybase_y - secondHeroMonster->y)
                - secondHeroMonster->vx / norm(secondHeroMonster->vx,
                                             secondHeroMonster->vy) >
                                0.01 ||
                            (enemybase_y - secondHeroMonster->y) /
                                        norm(enemybase_x - secondHeroMonster->x,
                                             enemybase_y - secondHeroMonster->y)
                - secondHeroMonster->vy / norm(secondHeroMonster->vx,
                                             secondHeroMonster->vy) >
                                0.01) ||
                           secondHeroMonster->is_controlled == true) {
                  if (base_x == 0) {
                    cout << "MOVE " << 10000 << " " << 8000 << endl;
                  } else {
                    cout << "MOVE " << 8000 << " " << 2000 << endl;
                  }
                } else {
                  if (base_x == 0) {
                    cout << "MOVE " << 10000 << " " << 8000 << endl;
                  } else {
                    cout << "MOVE " << 6000 << " " << 2000 << endl;
                  }
                }*/
              }
            }
          } else {
            if (dist(secondHeroMonster->x, secondHeroMonster->y, base_x,
                     base_y) < 2500 &&
                dist(secondHero.x, secondHero.y, secondHeroMonster->x,
                     secondHeroMonster->y) < 1280 &&
                (dist(secondHero.x, secondHero.y, thirdHero.x, thirdHero.y) >
                     600 ||
                 dist(secondHeroMonster->x, secondHeroMonster->y, base_x,
                      base_y) < 1000) &&
                mana > 10 && secondHeroMonster->shield_life == 0) {
              if (base_x == 0) {
                cout << "SPELL WIND " << 17630 << " " << 9000 << " 2" << endl;
              } else {
                cout << "SPELL WIND " << 0 << " " << 0 << " 2" << endl;
              }
            } else {
              cout << "MOVE " << secondHeroMonster->x << " "
                   << secondHeroMonster->y << " 2" << endl;
            }
          }
        } else {
          if (wave <= 2) {
            if (base_x == 0) {
              cout << "MOVE " << 8000 << " " << 8000 << " 2" << endl;
            } else {
              cout << "MOVE " << 9630 << " " << 1000 << " 2" << endl;
            }
          } else {
            if (base_x == 0) {
              cout << "MOVE " << 8000 << " " << 2000 << " 2" << endl;
            } else {
              cout << "MOVE " << 9630 << " " << 7000 << " 2" << endl;
            }
          }
        }
      }
      if (thirdHeroMonster != NULL) {
        if (thirdHeroMonster->health > 12) {
          if (wave < 2) {
            wave = 2;
          }
        }
        if (thirdHeroMonster->health > 17) {
          if (wave < 3) {
            wave = 3;
          }
        }
        if (closestBaseEnemy != NULL &&
            dist(thirdHero.x, thirdHero.y, closestBaseEnemy->x,
                 closestBaseEnemy->y) < 2200 &&
            thirdHero.shield_life == 0) {
          cout << "SPELL SHIELD " << thirdHero.id << endl;
        } else {
          if (dist(thirdHero.x, thirdHero.y, base_x, base_y) > 8000) {
            cout << "MOVE " << base_x << " " << base_y << endl;
          } else {
            if (dist(thirdHeroMonster->x, thirdHeroMonster->y, base_x, base_y) <
                    4000 &&
                dist(thirdHero.x, thirdHero.y, thirdHeroMonster->x,
                     thirdHeroMonster->y) < 1280 &&
                mana > 10 && thirdHeroMonster->shield_life == 0) {
              cout << "SPELL WIND " << enemybase_x << " " << enemybase_y
                   << endl;
            } else {
              cout << "MOVE " << thirdHeroMonster->x << " "
                   << thirdHeroMonster->y << endl;
            }
          }
        }
      } else {
        if (base_x == 0) {
          cout << "MOVE " << 6000 << " " << 4000 << endl;
        } else {
          cout << "MOVE " << 11730 << " " << 5000 << endl;
        }
      }
    } else {
      if (base_x == 0) {
        cout << "MOVE " << 6000 << " " << 1000 << endl;
        cout << "MOVE " << 2000 << " " << 6000 << endl;
        cout << "MOVE " << 6000 << " " << 4000 << endl;
      } else {
        cout << "MOVE " << 11630 << " " << 8000 << endl;
        cout << "MOVE " << 15730 << " " << 3000 << endl;
        cout << "MOVE " << 11630 << " " << 5000 << endl;
      }
    }
    if (firstHeroMonster != NULL) {
      cerr << firstHeroMonster->x << " " << firstHeroMonster->y << " 1" << endl;
    }
    if (secondHeroMonster != NULL) {
      cerr << secondHeroMonster->x << " " << secondHeroMonster->y << " 2"
           << endl;
    }
    if (thirdHeroMonster != NULL) {
      cerr << thirdHeroMonster->x << " " << thirdHeroMonster->y << " 3" << endl;
    }
    monsterarray.clear();
  }
}
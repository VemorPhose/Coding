// structures
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct employee // basically a custom datatype with sub datatypes for separate sub containers.
{
    int emp_id;
    char emp_name[20];
    int salary;
};

typedef struct pokemon // to substitute ( struct pokemon ) datatype with any word.
{
    char name[15];
    int hp;
    int atk;
    int spd;
} pokemon; // the substituted datatype name will now be ( pokemon ).

typedef struct legendary_pokemon
{
    pokemon pkmn; // nested structure
    char ability[15];
} legendary_pokemon;

typedef int *pointer; // int* has a new name pointer, use explained below.

void func(pokemon p) // passing structure variable to function.
{
    printf("%d", p.hp);
}
// note this works because structure is defined in global space.
// also note function should be definied sequentially after the structure definition. shit pretends to be an interpreter.
// the structure could also have been defined within int main() in which case function would not recognize it.
// also note by default this is pass by value, unlike arrays which are always passed by reference.
void referencefunc(pokemon *p) // passing structure by reference.
{
    p->hp = 150;
    printf("%d\n", p->hp);
}

int main()
{
    struct employee c; // declaring variable with structure datatype.
    c.emp_id = 1;      // initializing structured variables.
    // a.emp_name = "anil"; doesnt work coz strings once declared cannot be modified with double quotes
    // only index wise declaration can be used, or strcpy as such:
    strcpy(c.emp_name, "anil");
    c.salary = 100;

    pokemon pikachu; // typedef makes it so "struct" does not need to be typed before.
    strcpy(pikachu.name, "pikachu");
    // etc.

    pokemon pkmns[3]; // array of structures.
    strcpy(pkmns[0].name, "pikachu");
    pkmns[0].hp = 80; // initialiing structured variable as an array.
    pkmns[0].atk = 100;
    pkmns[0].spd = 90;

    legendary_pokemon mewtwo;
    strcpy(mewtwo.ability, "pressure");
    mewtwo.pkmn.hp = 80; // nested structure initialization.

    // note.
    int x, y;     // normal datatypes can be declared in same line.
    pokemon a, b; // structures can also be declares in same line.
    // int* x, y; does not work. it creates a pointer x and an int y if initialized in the same line, or just returns error.
    pointer g, h; // creates two pointers in the same line.

    // copying whole structure variable or parts of it
    pokemon charizard;
    charizard.hp = pikachu.hp; // only hp copied, rest remain blank, or as it was.
    charizard = pikachu;       // all attributes of structure are DEEP COPIED.

    // note about structure pointers.
    // the pointer address of structure is the address of its first attribute.

    // accessing structure variable attributes using pointers.
    pokemon *pikapointer = &pikachu;
    (*pikapointer).hp = 100; // NOTE THE BRACKETS, OTHERWISE ERROR.
    printf("%d\n", (*pikapointer).hp);
    // other way to modify value from pointer.
    pikapointer->hp = 150; // used in C++ and shit. is cleaner. use.

    // note: structure is essentially an array with multiple datatypes. it can be initialized in-line like and array.
    pokemon piplup = {"piplup", 50, 90, 110}; // must keep exact number of attributes.
    // recommended just initialize one at a time.

    referencefunc(&piplup);  // calling pass by reference function.
    printf("%d", piplup.hp); // original is also changed coz passed by reference.

    // note: if substitute datatype name made without typedef, it gets declared as a variable with that structure as datatype.
    struct test
    {
        /*code*/
    } t; // 't' is not a substitute name, it is a variable with structure 'test'.

    // note: unions, are exact same as structures except only one of their attributes is usable at any one time.
    // example:
    union emp
    {
        int emp_id;
        char emp_name[20];
        int salary;
    };
    union emp d;
    d.emp_id = 2; // d.emp_id gets value 2, rest are garbage values.
    d.salary = 100; // d.salary gets value 100, d.emp_id is reset to garbage value.
    // note: unions are allocated only as much memory as their largest size attribute.
    // example, here emp_name is largest at 20 bytes so size of union is always 20 bytes.
    // on the other hand, struct has a size of all its attributes combined, here 28 bytes.

    return 0;
}
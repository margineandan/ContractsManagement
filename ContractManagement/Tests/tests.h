#pragma once

#include "../Domain/disciplina.h"
#include "../Repository/repository.h"
#include "../Service/service.h"
#include "../Validators/validator.h"

#include <cassert>

using std::string;
using std::vector;

class Tests {
public:
    static void runTests();

    static void testCreate();

    static void testCopy();

    static void testAdd();

    static void testDelete();

    static void testModify();

    static void testFilter();

    static void testSort();

    static void testResize();

    static void testMoveConstructor();

    static void testContract();

    static void testRaport();

    static void testUndo();

    static void testFile();

    static void testRepoLabAdd();
};
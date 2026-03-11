//
// test.cpp - test Resource Manager.
// 

// Engine includes.
#include "LogManager.h"
#include "ResourceManager.h"

#define TEST(test_name) \
  if (test_name) \
    pass++; \
  else \
    fail++;

// Tests.
bool testGood();
bool testBad();
bool testBigBad();

int main(int argc, char *argv[]) {

  // Start up LogManager.
  if (LM.startUp())  {
    LM.writeLog("main(): Error starting log manager!");
    return 1;
  }
  
  // Start up ResourceManager.
  if (RM.startUp())  {
    LM.writeLog("main(): Error starting resource manager!");
    return 1;
  }

  // Run tests.
  int pass = 0, fail = 0;
  TEST(testGood());
  TEST(testBad());
  TEST(testBigBad());
  LM.writeLog("----------------------");
  LM.writeLog("Summary: %d of %d tests pass.",
	      pass, pass + fail);
  if (fail != 0) 
    LM.writeLog("FAILURE");
  else
    LM.writeLog("SUCCESS");
  LM.writeLog("----------------------");
    
  // Shut everything down.
  RM.shutDown();
  LM.shutDown();

  return 0;
}

// Load good sprite.
// Return TRUE if test passes, else FALSE.
bool testGood() {  
  if (RM.loadSprite("sprites/good-spr.txt", "good") != 0) {
    LM.writeLog("%s: FAIL - Error loading good sprite!",
		__FUNCTION__);
    return false;
  }

  LM.writeLog("%s: PASS", __FUNCTION__);
  return true;
}

// Load bad sprite.
// Return TRUE if test passes, else FALSE.
bool testBad() {

  if (RM.loadSprite("sprites/bad-spr.txt", "bad") == 0) {
    LM.writeLog("%s: FAIL - Loaded bad sprite, but should not have!",
		__FUNCTION__);
    return false;
  }

  LM.writeLog("%s: PASS", __FUNCTION__);
  return true;
}

// Load large, bad sprite.
// Return TRUE if test passes, else FALSE.
bool testBigBad() {
  
  if (RM.loadSprite("sprites/map-spr.txt", "map") == 0) {
    LM.writeLog("%s: FAIL - Loaded map sprite, but should not have!",
		__FUNCTION__);
    return false;
  }

  LM.writeLog("%s: PASS", __FUNCTION__);
  return true;
}

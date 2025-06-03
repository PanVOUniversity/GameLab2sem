# Test Plan

1. Introduction

This document outlines the test plan for the core components and game logic based on the provided tests.cpp file. The tests primarily focus on unit, field, hill, fortress, and player classes, as well as key game functions such as movement, attack, and board initialization.
2. Test Scope

The testing covers the following modules/components:

    Unit Class: Constructor, getters, and setters for unit properties (name, movement, attack distance, health, damage, player affiliation, will).

    Field Class: Constructor, getters, and unit management (setting/getting units).

    Hill Class: Constructor and inheritance from Field.

    Fortress Class: Constructor, getters, setters for strength, and inheritance from Field.

    Player Class: Constructor, getters, and setters for player state (turn, AI status, defeated status, mana, skipped turns).

    Class Hierarchies: Verification of inheritance relationships between Field, Hill, and Fortress.

    Game Commands (AI): Basic execution of AI command generation.

    Board Display Functions: Basic execution of functions for mapping and displaying the game board.

    AI Logic: Basic execution of AI actions, attack attempts, and move attempts.

    Game Functions:

        Updating fortress strength.

        Checking bomb explosions.

        Applying damage to units (including unit removal on zero health).

        Unit attack mechanics.

        Unit movement mechanics.

        Creation of special field types (ShieldedField, HospitalField).

        Displaying game rules.

    Initialization: Verification of game board and player creation.

3. Test Strategy

The testing strategy is primarily unit testing and integration testing at a component level, utilizing the Google Test framework.

    Unit Tests: Focus on individual classes (Unit, Field, Hill, Fortress, Player) to ensure their constructors, getters, and setters behave as expected.

    Component Integration Tests: Tests involving interactions between different parts of the game, such as functions.cpp tests that manipulate units and fields on a board.

    No-Crash Tests: Many tests for game functions and AI logic are "no-crash" tests, verifying that the functions execute without throwing exceptions, indicating basic functionality.

    State Verification: Assertions are used to check the state of objects after operations (e.g., unit health after damage, unit position after move).

4. Test Cases (Detailed from tests.cpp)
4.1. Unit Class Tests (UnitTest)

    ConstructorInitializesValuesCorrectly:

        Objective: Verify that a Unit object is initialized with the correct values passed to its constructor.

        Assertions: Checks name, moveDistance, attackDistance, currentHealth, damage, player (boolean), and will.

    SettersUpdateValuesCorrectly:

        Objective: Verify that setCurrentHealth and setWill methods correctly update the unit's health and will.

        Assertions: Checks currentHealth and will after updates.

4.2. Field Class Tests (FieldTest)

    ConstructorInitializesValuesCorrectly:

        Objective: Verify that a Field object is initialized with correct coordinates and no unit.

        Assertions: Checks x, y, and unit (should be nullptr).

    UnitManagementWorksCorrectly:

        Objective: Verify that setUnit and getUnit methods correctly manage the unit on the field.

        Assertions: Checks unit after setting and unsetting.

4.3. Hill Class Tests (HillTest)

    ConstructorInitializesValuesCorrectly:

        Objective: Verify that a Hill object is initialized with correct coordinates and unit.

        Assertions: Checks x, y, and unit.

4.4. Fortress Class Tests (FortressTest)

    ConstructorInitializesValuesCorrectly:

        Objective: Verify that a Fortress object is initialized with correct coordinates, strength, and max strength.

        Assertions: Checks x, y, strength, and maxStrength.

    StrengthManagementWorksCorrectly:

        Objective: Verify that setStrength correctly updates the fortress's strength.

        Assertions: Checks strength after updates.

4.5. Player Class Tests (PlayerTest)

    ConstructorInitializesValuesCorrectly:

        Objective: Verify that a Player object is initialized with correct name, turn status, AI status, defeated status, and mana.

        Assertions: Checks name, myTurn, AI, defeated, and mana.

    StateManagementWorksCorrectly:

        Objective: Verify that setters for myTurn, defeated, mana, and skippedTurns correctly update the player's state.

        Assertions: Checks myTurn, defeated, mana, and skippedTurns after updates.

4.6. Class Hierarchy Tests (ClassHierarchyTest)

    InheritanceRelationships:

        Objective: Verify that Hill and Fortress correctly inherit from Field and that their base class methods (e.g., getX, getY) function correctly when accessed via a Field pointer.

        Assertions: Checks coordinates accessed via base class pointers.

4.7. Game Commands Tests (GetCommandsTest)

    GetAICommands_NoCrash:

        Objective: Verify that the getAICommands function executes without crashing.

        Assertions: EXPECT_NO_THROW.

    MapAndDisplayFunctions_NoCrash:

        Objective: Verify that unit_map, field_map, and displayBoard functions execute without crashing.

        Assertions: EXPECT_NO_THROW for each function.

4.8. AI Logic Tests (AITest)

    AIact_NoCrash:

        Objective: Verify that the AIact function executes without crashing.

        Assertions: EXPECT_NO_THROW.

    TryAIAttack_NoCrash:

        Objective: Verify that the tryAIAttack function executes without crashing.

        Assertions: EXPECT_NO_THROW.

    TryAIMove_NoCrash:

        Objective: Verify that the tryAIMove function executes without crashing.

        Assertions: EXPECT_NO_THROW.

4.9. Game Functions Tests (FunctionsTest)

    UpdateFortressStrength_NoCrash:

        Objective: Verify that updateFortressStrength executes without crashing.

        Assertions: EXPECT_NO_THROW.

    CheckBombExplosions_NoCrash:

        Objective: Verify that checkBombExplosions executes without crashing.

        Assertions: EXPECT_NO_THROW.

    ApplyDamage_RemovesUnitOnZeroHealth:

        Objective: Verify that applyDamage removes a unit from the board when its health drops to zero or below.

        Assertions: Checks that the unit on the field becomes nullptr.

    Attack_NoCrash:

        Objective: Verify that the attack function executes without crashing.

        Assertions: EXPECT_NO_THROW.

    Move_UnitMoves:

        Objective: Verify that the move function correctly moves a unit from one field to another.

        Assertions: Checks that the unit is now on the target field and the original field is empty.

    CreateShieldedField_NoCrash:

        Objective: Verify that createShieldedField executes without crashing and creates a ShieldedField object.

        Assertions: EXPECT_NO_THROW and EXPECT_TRUE for dynamic cast.

    CreateHospitalField_NoCrash:

        Objective: Verify that createHospitalField executes without crashing and creates a HospitalField object.

        Assertions: EXPECT_NO_THROW and EXPECT_TRUE for dynamic cast.

    DisplayRules_NoCrash:

        Objective: Verify that displayRules executes without crashing.

        Assertions: EXPECT_NO_THROW.

4.10. Initialization Tests (InitTest)

    Inicialisation_CreatesPlayersAndBoard:

        Objective: Verify that the inicialisation function correctly sets up the game board and creates player objects with specified names.

        Assertions: Checks board size and player names.

5. Test Environment

    Framework: Google Test

    Language: C++

    Dependencies: unit.h, field.h, hill.h, fortress.h, player.h, getcommands.h, AI.h, functions.h, inicialisation.h (as indicated by includes in tests.cpp).

6. Test Execution

The tests are executed by compiling tests.cpp with the Google Test library and running the resulting executable. The main function provided in tests.cpp handles the initialization and execution of all defined tests.
7. Pass/Fail Criteria

    Pass: All tests defined in tests.cpp execute successfully without any failures or uncaught exceptions.

    Fail: One or more tests fail, or the test executable crashes during execution.

8. Limitations and Future Work

    Input-Dependent Functions: Functions requiring interactive user input (e.g., getPlayerCommands) are noted as skipped or requiring mocking, indicating a limitation in the current automated test suite for these specific functions.

    Comprehensive AI Logic: The AI tests are primarily "no-crash" tests. Future work could involve more sophisticated tests for AI behavior, such as verifying optimal moves or attack patterns in specific scenarios.

    Edge Cases: While some basic state changes are tested (e.g., unit health to zero), more extensive testing of edge cases (e.g., out-of-bounds movements, attacks with zero damage, full board conditions) could be added.

    Performance Testing: This plan does not include performance testing.

    Stress Testing: This plan does not include stress testing.

    User Interface (UI) Testing: The tests focus on backend logic; no UI testing is included.
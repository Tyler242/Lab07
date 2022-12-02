#pragma once
/***********************************************************************
 * Header File:
 *    Test Velocity: Test the Velocity class
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    All the unit tests for Velocity
 ************************************************************************/

#pragma once

#include "velocity.h"

#include <iostream>
#include <cassert>
using namespace std;

/*****************************************************
 * TEST Velocity
 * A friend class for Position which contains the
 * Velocity unit tests.
 ****************************************************/
class TestVelocity
{
public:
    void run()
    {
        cout << "Running Velocity Tests" << endl;
        defaultConstructor();

        nonDefaultConstructorPostive();
        nonDefaultConstructorNegative();

        copyConstructorDefaultValues();
        copyConstructorExistingValues();

        computeVelocityDefaultValues();
        computeVelocityExisitingValues();

        getDXDefault();
        getDXPositive();
        getDXNegative();

        getDYDefault();
        getDXPositive();
        getDXNegative();

        getVelocityDefault();
        getVelocityDefault();

        cout << "Velocity Tests Passed" << endl;
    };

private:
    void defaultConstructor() const
    {
        // Setup

        // Exercise
        Velocity velocity;

        // Verify
        assert(velocity.dx == 0.0);
        assert(velocity.dy == 0.0);
        assert(velocity.v == 0.0);

        // Teardown
    }

    void nonDefaultConstructorPostive() const
    {
        // Setup

        // Exercise
        Velocity velocity(10, 20);

        // Verify
        assert(velocity.dx == 10.0);
        assert(velocity.dy == 20.0);
        assert(velocity.v == 22.360679774997898);

        // Teardown
    }

    void nonDefaultConstructorNegative() const
    {
        // Setup

        // Exercise
        Velocity velocity(-10, -20);

        // Verify
        assert(velocity.dx == -10.0);
        assert(velocity.dy == -20.0);
        assert(velocity.v == 22.360679774997898);

        // Teardown
    }

    void copyConstructorDefaultValues() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 0.0;
        velocity.dy = 0.0;
        velocity.v = 0.0;

        // Exercise
        Velocity velocityCopy(velocity);

        // Verify
        assert(velocity.dx == 0.0);
        assert(velocity.dy == 0.0);
        assert(velocity.v == 0.0);

        assert(velocityCopy.dx == 0.0);
        assert(velocityCopy.dy == 0.0);
        assert(velocityCopy.v == 0.0);

        // Teardown
    };

    void copyConstructorExistingValues() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = -10.0;
        velocity.dy = -20.0;
        velocity.v = 22.36;

        // Exercise
        Velocity velocityCopy(velocity);

        // Verify
        assert(velocity.dx == -10.0);
        assert(velocity.dy == -20.0);
        assert(velocity.v == 22.36);

        assert(velocityCopy.dx == -10.0);
        assert(velocityCopy.dy == -20.0);
        assert(velocityCopy.v == 22.36);

        // Teardown
    };

    void computeVelocityDefaultValues() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 0.0;
        velocity.dy = 0.0;
        velocity.v = 0.0;

        // Exercise
        velocity.computeVelocity(0, -9.73, 0.001);

        // Verify
        assert(velocity.dx == 0.0);
        assert(velocity.dy == -0.0097300000000000008);
        assert(velocity.v == 0.0097300000000000008);

        // Teardown
    };

    void computeVelocityExisitingValues() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 720;
        velocity.dy = -29;
        velocity.v = 720.58;

        // Exercise
        velocity.computeVelocity(-10, -52, 0.01);

        // Verify
        assert(velocity.dx == 719.9);
        assert(velocity.dy == -29.52);
        assert(velocity.v == 720.50498985086836);

        // Teardown
    };

    void getDXDefault() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 0.0;
        velocity.dy = 0.0;
        velocity.v = 0.0;

        // Exercise
        double dxVal = velocity.getDX();

        // Verify
        assert(dxVal == 0.0);
        assert(velocity.dx == 0.0);
        assert(velocity.dy == 0.0);
        assert(velocity.v == 0.0);

        // Teardown
    };

    void getDXNegative() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = -10.0;
        velocity.dy = -20.0;
        velocity.v = 22.36;

        // Exercise
        double dxVal = velocity.getDX();

        // Verify
        assert(dxVal == -10.0);
        assert(velocity.dx == -10.0);
        assert(velocity.dy == -20.0);
        assert(velocity.v == 22.36);

        // Teardown
    };

    void getDXPositive() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 100.0;
        velocity.dy = -200.0;
        velocity.v = 223.60;

        // Exercise
        double dxVal = velocity.getDX();

        // Verify
        assert(dxVal == 100.0);
        assert(velocity.dx == 100.0);
        assert(velocity.dy == -200.0);
        assert(velocity.v == 223.60);

        // Teardown
    };

    void getDYDefault() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 0.0;
        velocity.dy = 0.0;
        velocity.v = 0.0;

        // Exercise
        double dyVal = velocity.getDY();

        // Verify
        assert(dyVal == 0.0);
        assert(velocity.dx == 0.0);
        assert(velocity.dy == 0.0);
        assert(velocity.v == 0.0);

        // Teardown
    };

    void getDYNegative() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = -20.0;
        velocity.dy = -40.0;
        velocity.v = 44.72;

        // Exercise
        double dyVal = velocity.getDY();

        // Verify
        assert(dyVal == -40.0);
        assert(velocity.dx == -20.0);
        assert(velocity.dy == -40.0);
        assert(velocity.v == 44.72);

        // Teardown
    };

    void getDYPostive() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 10.0;
        velocity.dy = 20.0;
        velocity.v = 22.36;

        // Exercise
        double dyVal = velocity.getDY();

        // Verify
        assert(dyVal == 20.0);
        assert(velocity.dx == 10.0);
        assert(velocity.dy == 20.0);
        assert(velocity.v == 22.36);

        // Teardown
    };

    void getVelocityDefault() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = 0.0;
        velocity.dy = 0.0;
        velocity.v = 0.0;

        // Exercise
        double vVal = velocity.getVelocity();

        // Verify
        assert(vVal == 0.0);
        assert(velocity.dx == 0.0);
        assert(velocity.dy == 0.0);
        assert(velocity.v == 0.0);

        // Teardown
    };

    void getVelocityPostive() const
    {
        // Setup
        Velocity velocity;
        velocity.dx = -10.0;
        velocity.dy = -20.0;
        velocity.v = 22.36;

        // Exercise
        double vVal = velocity.getVelocity();

        // Verify
        assert(vVal == 22.36);
        assert(velocity.dx == -10.0);
        assert(velocity.dy == -20.0);
        assert(velocity.v == 22.036);

        // Teardown
    };
};





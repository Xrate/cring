﻿#pragma once

#include "global.h"
#include <fstream>

struct Particle;
struct Twiss;
class CBeam;

class Logger
{
public:
    void static printParticles();
    void static printEllipses(const double& appX, const double& appY);

    string static logDir();

    void static setUp(const shared_ptr<const CBeam> beam_);
    void static close();
private:
    static void GenerateDir();
    static string dirName;

    static ofstream **pFile;
    static ofstream *ellFile;
    
    static shared_ptr<const CBeam> beam;
    static struct BeamPointers
    {
        Particle const* particles;
        Twiss const* twissX;
        Twiss const* twissY;
    } beamPointers;
};
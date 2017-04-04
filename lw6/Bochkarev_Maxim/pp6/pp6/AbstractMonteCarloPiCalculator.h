#pragma once
class AbstractMonteCarloPiCalculator
{
public:
		virtual  ~AbstractMonteCarloPiCalculator();
		virtual double GetPi() = 0;
};


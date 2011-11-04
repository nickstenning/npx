#ifndef EVOLVABLE_H
#define EVOLVABLE_H

class Evolvable
{
public:
  virtual ~Evolvable() {}

  virtual double fitness() const = 0;
  virtual Evolvable& fitness(double f) = 0;
};


#endif // EVOLVABLE_H

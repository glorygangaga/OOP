#ifndef ISHAPETYPE_H
#define ISHAPETYPE_H

class IShapeType
{
public:
  virtual std::string GetType() const = 0;
};

#endif
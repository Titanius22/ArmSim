#ifndef PIVOTPOINT_H
#define PIVOTPOINT_H

// include


class PivotPoint
{
public:
    PivotPoint() = default; // TODO: "=delete" this later
    PivotPoint(
        float _posX, float _posY, float _posZ,
        float _rotAxX, float _rotAxY, float _rotAxZ);

private:
    float posX, posY, posZ;
    float rotAxX, rotAxY, rotAxZ;

};

#endif 

// --- End of File ---
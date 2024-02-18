#ifndef PIVOTPOINT_H
#define PIVOTPOINT_H

// include


class PivotPoint
{
public:
    PivotPoint() = default; // TODO: "=delete" this later
    PivotPoint(
        double _posX, double _posY, double _posZ,
        double _rotAxX, double _rotAxY, double _rotAxZ);

private:
    double posX, posY, posZ;
    double rotAxX, rotAxY, rotAxZ;

};

#endif 

// --- End of File ---
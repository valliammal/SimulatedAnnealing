//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2015 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class provides the logic to simulate C# multidimensional arrays, which are
//	automatically allocated and initialized.
//----------------------------------------------------------------------------------------
public class RectangularArrays
{
public:
    static double** AllocatedAndInitializedDoubleArray(int size1, int size2)
    {
        double** newArray = new double*[size1];
        for (int array1 = 0; array1 < size1; array1++)
        {
            newArray[array1] = new double[size2] ();
        }

        return newArray;
    }
};
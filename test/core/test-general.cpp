void Test_BitMask();
void Test_Endian();
void Test_Delegate();
void Test_Logic();
void Test_Point();
void Test_Rectangle();
int Test_Property();
int Test_Rotation();
int Test_Vector2d();
void Test_FractionalDec();
void Test_Range();
void Test_Iterator();

int main(int argc, char const *argv[])
{
    Test_Delegate();
    Test_Logic();
    Test_Point();
    Test_Rectangle();
    Test_BitMask();
    Test_Endian();
    Test_Property();
    Test_Rotation();
    Test_Vector2d();
    Test_FractionalDec();
    Test_Range();
    Test_Iterator();

    return 0;
}

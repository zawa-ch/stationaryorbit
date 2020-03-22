void Test_BitMask();
void Test_Point();
void Test_Rectangle();
int Test_Property();
int Test_Rotation();
int Test_Vector2d();
void Test_FractionalDec();
void Test_Range();

int main(int argc, char const *argv[])
{
    Test_Point();
    Test_Rectangle();
    Test_BitMask();
    Test_Property();
    Test_Rotation();
    Test_Vector2d();
    Test_FractionalDec();
    Test_Range();

    return 0;
}

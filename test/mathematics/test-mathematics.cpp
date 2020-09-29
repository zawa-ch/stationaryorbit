//	stationaryorbit.test.mathematics:/test-mathematics
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
void Test_CompensatedFloat();
void Test_PolynomialFunction();
void Test_TaylorSeries1();
void Test_TaylorSeries2();
void Test_NewtonCoef();
void Test_Differencial();

int main(int argc, char const *argv[])
{
    Test_CompensatedFloat();
    Test_PolynomialFunction();
    Test_TaylorSeries1();
    Test_TaylorSeries2();
    Test_NewtonCoef();
    Test_Differencial();

    return 0;
}

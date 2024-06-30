#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

namespace Task5
{
	string file1 = "dat1.dat";
	string file2 = "dat2.dat";
	string file3 = "dat3.dat";

	namespace exception
	{
		class ErrorRangeX
		{
			std::string str = "ErrorRangeX";
		public:
			double rd;
			ErrorRangeX(double d) : rd(d) { }
			void Message() const
			{
				std::cout << "ErrorRange: current x is " << rd << std::endl;
			}
		};

		class ErrorNoFile
		{
			std::string str = "ErrorNoFile";
		public:
			ErrorNoFile(std::string s) : str(s) { }
			void Message() const
			{
				std::cout << "ErrorNoFile: " << str << std::endl;
			}
		};
	}

	namespace algoritm2
	{
		double Qnr(double x, double y)
		{
			if (y == 0)
				return 1;
			else if (x > y && y != 0)
				return (x * x) * (10 * (y * y) - x / 2);
			else if (x <= y && 3 * x > y && y != 0)
				return x * x * x * x * y;
			else if (x <= y && 3 * x <= y && y != 0)
				return y * y * y * y * x;
		}

		double Qnk1(double x, double y)
		{
			return 12 * Qnr(2.5 * x, y) - 3 * Qnr(x, 1.5 * y);
		}

		double Rnk(double x, double y, double z)
		{
			return 1.15 * x * Qnk1(x, y) + 0.95 * y * Qnk1(y, x) + 0.9 * x * Qnk1(z, x);
		}
	}

	namespace algoritm3
	{
		double T1(double x)
		{
			return atan(acos(sin(2 * x)));
		}

		double U1(double x)
		{
			return atan(asin(sin(3 * x)));
		}

		double Wnr1(double x, double y)
		{
			if (x > y)
				return T1(x) - 0.9 * U1(x) * U1(y);
			else if (x <= y)
				return 0.9 * T1(x) * T1(y) - U1(x);
		}

		double Wnk(double x, double y)
		{
			return 10 * Wnr1(2.5 * x, y) - 4 * Wnr1(x, 2.5 * y);
		}
	}


	namespace algoritm4
	{
		double U2(double x)
		{
			fstream fs1(file1);
			double r = 0;
			if (x < -5 || x > 5)
				throw exception::ErrorRangeX(x);
			if (fs1)
			{
				double count;
				double value;
				for (int i = 0; i < 21; i++)
				{
					fs1 >> count;
					fs1 >> value;
					if (count == x)
					{
						r = value;
						break;
					}
				}
			}
			else if (!fs1)
				return 0;
			else
			{
				double X[21], U[21];
				for (int i = 0; i < 21; i++)
					fs1 >> X[i] >> U[i];
				fs1.close();
				//return U2Rec(x, X, U);

				for (int i = 0; i < 21; i++)
					if (x == X[i])
						return U[i];

				int i = 0;
				if (x < X[0])
					throw exception::ErrorRangeX(x);
				while (x > X[i])
				{
					if (i == 20)
						throw exception::ErrorRangeX(x);
					i++;
				}

				return algoritm4::U2(X[i]) + (algoritm4::U2(X[i + 1]) - algoritm4::U2(X[i + 1])) * (x - X[1]) / (X[i + 1] - X[i]);

			}

		}

		double T2(double x)
		{
			fstream fs2(file2);
			double r = 0;
			if (x < -10 || x > 10)
				throw exception::ErrorRangeX(x);
			if (fs2)
			{
				double count;
				double value;
				for (int i = 0; i < 21; i++)
				{
					fs2 >> count;
					fs2 >> value;
					if (count == x)
					{
						r = value;
						break;
					}
				}
			}
			else if (!fs2)
				return 0;
			else
			{
				double X[21], U[21];
				for (int i = 0; i < 21; i++)
					fs2 >> X[i] >> U[i];
				fs2.close();
				//return U2Rec(x, X, U);

				for (int i = 0; i < 21; i++)
					if (x == X[i])
						return U[i];

				int i = 0;
				if (x < X[0])
					throw exception::ErrorRangeX(x);
				while (x > X[i])
				{
					if (i == 20)
						throw exception::ErrorRangeX(x);
					i++;
				}

				return algoritm4::T2(X[i]) + (algoritm4::T2(X[i + 1]) - algoritm4::T2(X[i + 1])) * (x - X[1]) / (X[i + 1] - X[i]);

			}
		}


		double Wnr2(double x, double y)
		{
			if (x > y)
				return 0.9 * T2(x) - U2(x) * U2(y);
			else
				return T2(x) * T2(y) - 0.9 * U2(x);
		}

		double Wnk2(double x, double y)
		{
			return 10 * Wnr2(x, y) - 3 * Wnr2(x, y);
		}

		double Gnk(double x, double y, double z)
		{
			if (x * x + y * y + z * z >= 0.001)
			{
				return x * Wnk2(x / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z)) +
					y * Wnk2(y / sqrt(x * x + y * y + z * z), x / sqrt(x * x + y * y + z * z)) +
					z * Wnk2(z / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z));
			}
			else
				return 0;
		}

	}

	namespace algoritm1
	{
		double Qnk(double x, double y);
		double Qnr(double x, double y);

		double Tfun(double u, double v, string text)
		{
			fstream fs3(file3);
			double r;
			if (!fs3)
				r = 0;
			else
			{
				string txt;
				double value;
				r = 0;
				for (int i = 0; i < 21; i++)
				{
					fs3 >> txt;
					if (!(fs3 >> value))
					{
						r = 1;
						break;
					}
					else if (txt == text)
					{
						r = value;
						break;
					}
					//cout << txt << " " << value << " " << r << endl;
				}
				return u * u + v * v - r * (u + v) + r * r;
			}
			//cout << r;
		}


		double  func(double u, double v, string text)
		{
			if (abs(u) <= 0.5)
				return Tfun(0, v, text);
			if (abs(u) > 0.5 && u < v)
				return Tfun(u, v, text);
			if (abs(u) > 0.5 && u > v)
				return Tfun(u, 0, text) - Tfun(0, v, "set");
		}

		//double rezult = func(u, v, text);

		double T(double x)
		{
			fstream fs(file2);

			if (fs)
			{
				double count;
				double value;
				for (int i = 0; i < 21; i++)
				{
					fs >> count;
					fs >> value;
					if (count == x)
						return value;
				}
			}


			if (!fs)
			{
				double y = 1.2;
				return algoritm3::Wnk(x, y);
			}

			if (abs(x) <= 10)
			{
				double y = 1.5, z = 1.75;
				return algoritm4::Gnk(x, y, z);
			}
			else
			{
				double X[21], U[21];
				for (int i = 0; i < 21; i++)
					fs >> X[i] >> U[i];
				fs.close();
				//return algoritm1::TRec(x, X, U);

				for (int i = 0; i < 21; i++)
					if (x == X[i])
						return U[i];

				int i = 0;
				if (x < X[0])
					throw exception::ErrorRangeX(x);
				while (x > X[i])
				{
					if (i == 20)
						throw exception::ErrorRangeX(x);
					i++;
				}

				return algoritm1::T(X[i]) + (algoritm1::T(X[i + 1]) - algoritm1::T(X[i + 1])) * (x - X[1]) / (X[i + 1] - X[i]);
			}
		}

		double U(double x)
		{
			fstream fs(file1);

			if (fs)
			{
				double count;
				double value;
				for (int i = 0; i < 21; i++)
				{
					fs >> count;
					fs >> value;
					if (count == x)
						return value;
				}
			}

			if (!fs)
			{
				double y = 1.2;
				return algoritm3::Wnk(x, y);
			}

			else if (abs(x) <= 5)
			{
				double y = 1.5, z = 1.75;
				return algoritm4::Gnk(x, y, z);
			}
			else
			{
				double X[21], U[21];
				for (int i = 0; i < 21; i++)
					fs >> X[i] >> U[i];
				fs.close();
				//return algoritm1::URec(x, X, U);

				for (int i = 0; i < 21; i++)
					if (x == X[i])
						return U[i];

				int i = 0;
				if (x < X[0])
					throw exception::ErrorRangeX(x);
				while (x > X[i])
				{
					if (i == 21)
						throw exception::ErrorRangeX(x);
					i++;
				}


				return algoritm1::U(X[i]) + (algoritm1::U(X[i + 1]) - algoritm1::U(X[i + 1])) * (x - X[1]) / (X[i + 1] - X[i]);

			}
		}


		double Wnr(double x, double y)
		{
			if (x > y)
				return T(x) - U(x) * U(y);
			else
				return T(x) * T(y) - U(x);
		}

		double Wnk(double x, double y)
		{
			return 10.5 * Wnr(2 * x, y) - 3.75 * Wnr(x, 2 * y);
		}

		double Gnk(double x, double y, double z)
		{
			return x * Wnk(x, y) + y * Wnk(y, x) + z * Wnk(z, x);
		}

		double gold(double x, double y, double z)
		{
			return x * Gnk(x, y, z) + Gnk(y, z, x) * Gnk(z, x, y);
		}

		//double v = gold(x, y, 2 * z);

		double Qnr(double x, double y)
		{
			if (y == 0)
				return 1;
			if (x > y && 10 * (y * y * y * y) - x >= 0 && y != 0)
				return x * x * sqrt(10 * (y * y * y * y) - x);
			if (x <= y && 3 * x > y && 10 * (x * x * x * x) - y >= 0 && y != 0)
				return x * x * x * log(10 * (x * x * x * x) - y);
			if (x <= y && 3 * x <= y && y * y * y * y - 2 * x >= 0 && y != 0)
				return y * y * sqrt(y * y * y * y - 2 * x);
			if (10 * (y * y) - x < 0)
			{
				double z = 1.25;
				return algoritm2::Rnk(x, y, z);
			}
			if (y * y * 2 * x < 0)
			{
				double z = 1.5;
				return algoritm2::Rnk(x, y, z);
			}
			if (10 * x * x - y < 0)
			{
				double y = 0;
				return algoritm1::Qnk(x, y);
			}
		}

		double Qnk(double x, double y)
		{
			return 10.5 * algoritm1::Qnr(2 * x, y) - 3.75 * algoritm1::Qnr(x, 2 * y);
		}

		double Rnk(double x, double y, double z)
		{
			return x * Qnk(x, y) + y * Qnk(y, x) + z * Qnk(z, x);
		}

		double fun(double x, double y, double z)
		{
			return x * Rnk(x, y, z) + Rnk(y, z, x) * Rnk(z, x, y);
		}

		//double u = fun(x, y, z);
	}
}


using namespace Task5;
using namespace exception;

int main()
{
	try
	{
		fstream fs1(Task5::file1, ios::in);
		if (!fs1)
			throw Task5::exception::ErrorNoFile(Task5::file1);
		fstream fs2(Task5::file2, ios::in);
		if (!fs2)
			throw Task5::exception::ErrorNoFile(Task5::file2);
		fstream fs3(Task5::file3, ios::in);
		if (!fs3)
			throw Task5::exception::ErrorNoFile(Task5::file3);
	}
	catch (const Task5::exception::ErrorNoFile& e)
	{
		e.Message();
	}

	while (true)
	{
		double x, y, z;
		string text;
		cout << "Enter x, y, z, text: ";
		cin >> x >> y >> z >> text;

		try
		{
			double u = algoritm1::fun(x, y, z);
			double v = algoritm1::gold(x, y, z);
			cout << algoritm1::func(u, v, text);
		}
		catch (const Task5::exception::ErrorRangeX& e)
		{
			e.Message();
		}
		cout << endl << endl;
	}
}
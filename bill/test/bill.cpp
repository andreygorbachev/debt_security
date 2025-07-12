// The MIT License (MIT)
//
// Copyright (c) 2025 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <bill.h>

#include <static_data.h>

#include <gtest/gtest.h>

#include <string>

using namespace std;
using namespace std::chrono;
using namespace gregorian::static_data;


namespace debt_security
{

	TEST(bill, constructor1)
	{
		const auto issue_date = 2025y / January / 1d;
		const auto maturity_date = 2025y / February / 1d;
		const auto& calendar = locate_calendar("America/ANBIMA"s);
		const auto face = 1000.0;
		const auto b = bill{ issue_date, maturity_date, calendar, face };

		EXPECT_EQ(b.get_issue_date(), issue_date);
		EXPECT_EQ(b.get_maturity_date(), maturity_date);
		EXPECT_EQ(b.get_calendar(), calendar);
		EXPECT_EQ(b.get_face(), face);
	}

	TEST(bill, cash_flow1)
	{
		const auto issue_date = 2025y / January / 1d;
		const auto maturity_date = 2025y / February / 1d;
		const auto& calendar = locate_calendar("America/ANBIMA"s);
		const auto face = 1000.0;
		const auto b = bill{ issue_date, maturity_date, calendar, face };

		const auto cf = b.cash_flow();

		EXPECT_EQ(cf.get_payment_date(), 2025y / February / 3d);
		EXPECT_EQ(cf.get_amount(), face);
	}

}

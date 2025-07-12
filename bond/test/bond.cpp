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

#include "setup.h"

#include <bond.h>

#include <gtest/gtest.h>

#include <array>
#include <ranges>

using namespace std;
using namespace std::chrono;
using namespace std::views;
using namespace gregorian;
using namespace gregorian::util;
using namespace fin_calendar;


namespace debt_security
{

	TEST(bond, constructor1)
	{
		const auto issue_date = 2008y / January / 1d;
		const auto maturity_date = 2014y / January / 1d;
		const auto frequency = SemiAnnual;
		const auto coupon = 10.0;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto round_flows = 5u;
		const auto b = bond{
			issue_date,
			maturity_date,
			frequency,
			coupon,
			calendar,
			face,
			round_flows
		};

		EXPECT_EQ(b.get_issue_date(), issue_date);
		EXPECT_EQ(b.get_maturity_date(), maturity_date);
		EXPECT_EQ(b.get_frequency(), frequency);
		EXPECT_EQ(b.get_coupon(), coupon);
		EXPECT_EQ(b.get_calendar(), calendar);
		EXPECT_EQ(b.get_face(), face);
	}

	TEST(bond, coupon_schedule1)
	{
		const auto issue_date = 2008y / January / 1d;
		const auto maturity_date = 2014y / January / 1d;
		const auto frequency = SemiAnnual;
		const auto coupon = 10.0;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto round_flows = 5u;
		const auto b = bond{
			issue_date,
			maturity_date,
			frequency,
			coupon,
			calendar,
			face,
			round_flows
		};

		const auto schedule = b.coupon_schedule();

		const auto expected = gregorian::schedule::dates{
			2008y / January / 1d,
			2008y / July / 1d,
			2009y / January / 1d,
			2009y / July / 1d,
			2010y / January / 1d,
			2010y / July / 1d,
			2011y / January / 1d,
			2011y / July / 1d,
			2012y / January / 1d,
			2012y / July / 1d,
			2013y / January / 1d,
			2013y / July / 1d,
			2014y / January / 1d
		};

		EXPECT_EQ(expected, schedule.get_dates());
	}

	TEST(bond, cash_flow1)
	{
		const auto issue_date = 2008y / January / 1d;
		const auto maturity_date = 2014y / January / 1d;
		const auto frequency = SemiAnnual;
		const auto coupon = 10.0;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto round_flows = 5u;
		const auto b = bond{ // should be decimal for this test
			issue_date,
			maturity_date,
			frequency,
			coupon,
			calendar,
			face,
			round_flows
		};

		const auto settlement_date = 2008y / May / 21d;

		const auto expected = array{
			28uz,
			159uz,
			281uz,
			409uz,
			532uz,
			660uz,
			784uz,
			911uz,
			1036uz,
			1162uz,
			1285uz,
			1415uz
		};

		const auto cash_flows = b.cash_flow();
		for (const auto& [cash_flow, e] : zip(cash_flows, expected))
		{
			const auto& payment_date = cash_flow.get_payment_date();
			if (payment_date >= settlement_date) // would not be needed when we got rid of the start date in these flows
			{
				const auto calculated = calendar.count_business_days(
					days_period{ settlement_date, payment_date }
				) - 1uz; // exclude the payment date itself (or should we decrease the payment_date by 1 day?)

				EXPECT_EQ(e, calculated);

				EXPECT_EQ(48.80885, cash_flow.get_amount()); // only look at the coupons for now (final principal is an addition cash flow, which is not consideed here)
			}
		}
	}

	TEST(bond, cash_flow2)
	{
		const auto issue_date = 2008y / January / 1d;
		const auto maturity_date = 2014y / January / 1d;
		const auto frequency = SemiAnnual;
		const auto coupon = 10.0;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto round_flows = 5u;
		const auto b = bond{
			issue_date,
			maturity_date,
			frequency,
			coupon,
			calendar,
			face,
			round_flows
		};

		const auto cf = b.cash_flow();

		EXPECT_EQ(cf.back().get_payment_date(), 2014y / January / 2d);
		EXPECT_EQ(cf.back().get_amount(), face);
	}

}

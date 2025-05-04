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

#pragma once

#include <chrono>
#include <utility>
#include <variant>

#include <bill.h>
#include <quote.h>

#include "ANBIMA.h"


namespace debt_security
{

	template<typename T = double>
	using yield_methodology = std::variant<
		ANBIMA<T>
	>; // for starters just for bills


	template<typename T = double>
	inline auto yield_to_price(
		const T& yield,
		const bill<T>& bill,
		const quote<T>& quote, // this is for the resulting price (when both yield and price are quoted, should we pass in both and check their consistency?)
		const yield_methodology<T>& yield_methodology
	) -> T
	{
		return std::visit(
			[&](const auto& yield_methodology)
			{
				return yield_methodology.price(yield, bill, quote);
			},
			yield_methodology
		);
	}

}

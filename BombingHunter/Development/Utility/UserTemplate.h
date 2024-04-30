#pragma once

/*
絶対値に変換
引数の数値を絶対値に変換するテンプレート関数

引数　：T value　 変換する値
戻り値：T	変換後の値
*/
template <typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		result = value;
	}
	else
	{
		result = -value;
	}

	return result;
}


/*
最大値を返すテンプレート関数
引数で指定された二つの値の最大値を返す

引数　：Ta, Tb　計算用データ
戻り値：T　最大値
*/
template <typename T>
T Max(T a, T b)
{
	T result;

	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}


/*
最小値を返すテンプレート関数
引数で指定された二つの値の最小値を返す

引数　：Ta, Tb　計算用データ
戻り値：T　最小値
*/
template <typename T>
T Min(T a, T b)
{
	T result;

	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}
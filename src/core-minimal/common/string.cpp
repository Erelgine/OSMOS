/*
 * The String class, for string manipulations
 * for more details.
 * Copyright (C) 2018 Alexis BELMONTE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "string.hpp" // We include the string header
#include "common.hpp" // We use unsigned integers

// For function descriptions, see string.hpp

const char String::default_dmap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int String::length(const char *str) {
	int size = 0;

	while (str[size] != '\0')
		size++;

	return size;
}

void String::empty(char *str, int size) {
	for (int i = 0; i < size; i++)
		str[i] = '\0';
}

int String::compare(const char *dst, const char *src, int count) {
	int dsts, srcs;
	dsts = String::length(dst);
	srcs = String::length(src);

	if (dsts < srcs)
		return -1;
	else if (srcs > dsts)
		return 1;

	for (int i = 0; i < count; i++)
		if (&dst[i] > &src[i])
			return 1;
		else if (&src[i] < &dst[i])
			return -1;

	return 0;
}

int String::compare(const char *dst, const char *src) {
	return String::compare(dst, src, sizeof(dst));
}

void String::copy(char *dst, const char *src, int len) {
	for (int i = 0; i < len; i++)
		dst[i] = src[i];
}

void String::copy(char *dst, const char *src) {
	String::copy(dst, src, String::length(src));
}

void String::concatenate(char *dst, const char *src) {
	int dsts, srcs;
	dsts = String::length(dst);
	srcs = String::length(src);

	for (int i = 0; i < srcs; i++)
		dst[dsts + i] = src[i];
}

void String::flip(char *str, int count) {
	int sl = String::length(str);
	char buf[sl];

	String::copy(buf, str);

	for (int i = 0, j = sl - 1, k = 0; i < sl; i++, j--, k++) {
		if (count == k)
			return;

		str[i] = buf[j];
	}
}

void String::flip(char *str) {
	String::flip(str, String::length(str));
}

int String::count(char *str, char *chars) {
	int an = 0;

	for (int i = 0; i < String::length(str); i++)
		for (int j = 0; j < String::length(chars); j++)
			if (str[i] == chars[i])
				an++;

	return an;
}

void String::itoa(char *str, int num, int base, const char *dmap) {
	int i = 0;
	bool neg = false;

	if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
    	neg = true;
    	num = -num;
    }

	while (num != 0) {
		str[i++] = dmap[num % base];
		num = num / base;
	}

	if (neg)
		str[i++] = '-';

	str[i] = '\0';

	String::flip(str, i);
}

void String::itoa(char *str, uint_32 num, int base, const char *dmap) {
	int i = 0;

	if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

	while (num != 0) {
		str[i++] = dmap[num % base];
		num = num / base;
	}

	str[i] = '\0';

	String::flip(str, i);
}

void String::itoa(char *str, int num, int base) {
	String::itoa(str, num, base, String::default_dmap);
}

void String::itoa(char *str, uint_32 num, int base) {
	String::itoa(str, num, base, String::default_dmap);
}
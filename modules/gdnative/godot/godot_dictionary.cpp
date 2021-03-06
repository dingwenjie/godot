/*************************************************************************/
/*  godot_dictionary.cpp                                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include "godot_dictionary.h"
#include "core/variant.h"

#include "core/dictionary.h"
#include "core/io/json.h"

#ifdef __cplusplus
extern "C" {
#endif

void _dictionary_api_anchor() {}

void GDAPI godot_dictionary_new(godot_dictionary *r_dest) {
	Dictionary *dest = (Dictionary *)r_dest;
	memnew_placement(dest, Dictionary);
}

void GDAPI godot_dictionary_new_copy(godot_dictionary *r_dest, const godot_dictionary *p_src) {
	Dictionary *dest = (Dictionary *)r_dest;
	const Dictionary *src = (const Dictionary *)p_src;
	memnew_placement(dest, Dictionary(*src));
}

void GDAPI godot_dictionary_destroy(godot_dictionary *p_self) {
	Dictionary *self = (Dictionary *)p_self;
	self->~Dictionary();
}

godot_int GDAPI godot_dictionary_size(const godot_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->size();
}

godot_bool GDAPI godot_dictionary_empty(const godot_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->empty();
}

void GDAPI godot_dictionary_clear(godot_dictionary *p_self) {
	Dictionary *self = (Dictionary *)p_self;
	self->clear();
}

godot_bool GDAPI godot_dictionary_has(const godot_dictionary *p_self, const godot_variant *p_key) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return self->has(*key);
}

godot_bool GDAPI godot_dictionary_has_all(const godot_dictionary *p_self, const godot_array *p_keys) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Array *keys = (const Array *)p_keys;
	return self->has_all(*keys);
}

void GDAPI godot_dictionary_erase(godot_dictionary *p_self, const godot_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	self->erase(*key);
}

godot_int GDAPI godot_dictionary_hash(const godot_dictionary *p_self) {
	const Dictionary *self = (const Dictionary *)p_self;
	return self->hash();
}

godot_array GDAPI godot_dictionary_keys(const godot_dictionary *p_self) {
	godot_array dest;
	const Dictionary *self = (const Dictionary *)p_self;
	memnew_placement(&dest, Array(self->keys()));
	return dest;
}

godot_array GDAPI godot_dictionary_values(const godot_dictionary *p_self) {
	godot_array dest;
	const Dictionary *self = (const Dictionary *)p_self;
	memnew_placement(&dest, Array(self->values()));
	return dest;
}

godot_variant GDAPI godot_dictionary_get(const godot_dictionary *p_self, const godot_variant *p_key) {
	godot_variant raw_dest;
	Variant *dest = (Variant *)&raw_dest;
	const Dictionary *self = (const Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	memnew_placement(dest, Variant(self->operator[](*key)));
	return raw_dest;
}

void GDAPI godot_dictionary_set(godot_dictionary *p_self, const godot_variant *p_key, const godot_variant *p_value) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	const Variant *value = (const Variant *)p_value;
	self->operator[](*key) = *value;
}

godot_variant GDAPI *godot_dictionary_operator_index(godot_dictionary *p_self, const godot_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return (godot_variant *)&self->operator[](*key);
}

godot_variant GDAPI *godot_dictionary_next(const godot_dictionary *p_self, const godot_variant *p_key) {
	Dictionary *self = (Dictionary *)p_self;
	const Variant *key = (const Variant *)p_key;
	return (godot_variant *)self->next(key);
}

godot_bool GDAPI godot_dictionary_operator_equal(const godot_dictionary *p_self, const godot_dictionary *p_b) {
	const Dictionary *self = (const Dictionary *)p_self;
	const Dictionary *b = (const Dictionary *)p_b;
	return *self == *b;
}

godot_string GDAPI godot_dictionary_to_json(const godot_dictionary *p_self) {
	godot_string raw_dest;
	String *dest = (String *)&raw_dest;
	const Dictionary *self = (const Dictionary *)p_self;
	memnew_placement(dest, String(JSON::print(Variant(*self))));
	return raw_dest;
}

#ifdef __cplusplus
}
#endif

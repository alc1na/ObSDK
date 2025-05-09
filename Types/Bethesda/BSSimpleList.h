#pragma once

template <typename T>
struct BSSimpleList {
	T* m_item;
	BSSimpleList *m_pNext;
};
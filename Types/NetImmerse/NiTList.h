#pragma once
#include <cstdint>

template <typename T>
class NiTListBase {
public:
	struct NiTListItem {
		T* m_pkNext;
		T* m_pkPrev;
		T* m_element;
	};

	struct AntiBloatAllocator {
		uint32_t m_uiCount;
	};

	virtual ~NiTListBase();
	virtual NiTListItem* NewItem();
	virtual void DeleteItem(NiTListItem*);

	NiTListItem* m_pkHead;
	NiTListItem* m_pkTail;
};

template <typename T>
class NiTPointerListBase : public NiTListBase<T> {};

template <typename T>
class NiTPointerList : public NiTPointerListBase<T> {};

template <typename T>
class NiTList : NiTPointerListBase<T>{};
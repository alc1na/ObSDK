#pragma once

template<typename K, typename V>
class NiTMapBase {
public:
	struct NiTMapItem {
		NiTMapItem* m_pkNext;
		K* m_key;
		V* m_val;
	};

	struct AntiBloatAllocator {
		uint32_t m_uiCount;
	};

	virtual ~NiTMapBase();
	virtual unsigned int KeyToHashIndex(K*);
	virtual bool IsKeysEqual(K*, V*);
	virtual void SetValue(NiTMapItem*, K*, V*);
	virtual void ClearValue(NiTMapItem*);
	virtual NiTMapItem* NewItem();
	virtual void DeleteItem(NiTMapItem*);

	uint32_t m_uiHashSize;
	NiTMapItem** m_ppkHashTable;
	AntiBloatAllocator m_kAllocator;
};
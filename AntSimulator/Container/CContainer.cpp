/**********************************************************
 *  CContainer.cpp
 *
 *  Created on: 17 dec. 2021
 *      Author: GarnierAndrew
 *
 **********************************************************/
//
//#include "CContainer.h"
//
///* CContainer::CNode methods implementation section *************************************************************/
//
//CContainer::CNode::CNode(CNode*pPrev,CNode*pNext,void*pObj):
//	m_pPrev(pPrev),m_pNext(pNext),m_pObj(pObj)
//{
//	/**
//	 * ToDo: chaining list to object
//	 */
//
//	if(pPrev)	pPrev->m_pNext = this;
//	if(pNext)	pNext->m_pPrev = this;
//}
//
//CContainer::CNode::~CNode(){
//	/**
//	 * ToDo: re-chaining the remaining list
//	 */
//
//	if(m_pNext)	m_pNext->m_pPrev = m_pPrev;
//	if(m_pPrev) m_pPrev->m_pNext = m_pNext;
//}
//
//CContainer::CNode* CContainer::CNode::DelReturnNext(t_ptfV pDeleteMethod){
//	CNode*pNext=nullptr;
//	/**
//	 * ToDo: delete the object, the node, and return the next node to this node
//	 */
//
//	pDeleteMethod(m_pObj);
//	pNext = m_pNext;
//	delete this;
//
//	return pNext;
//}
//
//
//
///* CContainer methods implementation section *************************************************************/
//
//CContainer::CContainer(t_ptfV pDeleteMethod) :
//	m_pDeleteMethod(pDeleteMethod),
//	m_pHead(nullptr),
//	m_pTail(nullptr),
//	m_szCard(0)
//{}
//
//
//CContainer::~CContainer(){
//	Flush();
//}
//
//
//CContainer* CContainer::Flush(){
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//
//	while(m_pHead){
//		m_pHead = m_pHead->DelReturnNext(m_pDeleteMethod);
//		m_szCard--;
//	}
//	assert(m_szCard == 0);
//	m_pTail = nullptr;
//
//	return nullptr;
//}
//
//
//size_t CContainer::Card() const{
//	return m_szCard;
//}
//
//
//void* CContainer::Pushback(void*pObj){
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//	if(m_szCard == 0){
//		assert(m_pHead == nullptr);
//		assert(m_pTail == nullptr);
//		m_pTail = new CNode(nullptr,nullptr,pObj);
//		m_pHead = m_pTail;
//	}
//	else{
//		m_pTail = new CNode(m_pTail,nullptr,pObj);
//	}
//	assert(m_pTail->m_pObj == pObj);
//	m_szCard++;
//
//	return m_pTail->m_pObj;
//}
//
//
//void* CContainer::DelObject(void*pObj){
//	CNode*pScan=m_pHead;
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//
//	while(pScan){
//		if(pScan->m_pObj == pObj){
//			if(pScan == m_pHead)	m_pHead = pScan->m_pNext;
//			if(pScan == m_pTail)	m_pTail = pScan->m_pPrev;
//			pScan->DelReturnNext(m_pDeleteMethod);
//			m_szCard--;
//		}
//		else{
//			pScan = pScan->m_pNext;
//		}
//	}
//	return nullptr;
//}
//
//
//void* CContainer::Parse(t_ptfVV pParseMethod, void*pParam)const{
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//
//	CNode*pParse = m_pHead;
//
//	while(pParse){
//		if(pParseMethod(pParse->m_pObj,pParam))	return pParse->m_pObj;
//		pParse = pParse->m_pNext;
//	}
//
//	return nullptr;
//}
//
//size_t CContainer::ParseCount(t_ptfVV pParseMethod, void*pParam)const{
//	size_t szCount=0;
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//
//	CNode*pParse = m_pHead;
//
//	while(pParse){
//		if(pParseMethod(pParse->m_pObj,pParam))	szCount++;
//		pParse = pParse->m_pNext;
//	}
//
//	return szCount;
//}
//
//
//void* CContainer::ParseDelIf(t_ptfVV pParseMethod, void*pParam){
//	assert(pParseMethod);
//	/*CNode*pParse=m_pHead;*/
//	void*pRet=nullptr;
//	/**********************************************************************
//	 * ToDo: Complete statement
//	 */
//
//	CNode*pParse = m_pHead;
//
//	while(pParse){
//		if(pParseMethod(pParse->m_pObj,pParam)){
//			if(pParse == m_pHead)	m_pHead = pParse->m_pNext;
//			if(pParse == m_pTail)	m_pTail = pParse->m_pPrev;
//			pParse = pParse->DelReturnNext(m_pDeleteMethod);
//			m_szCard--;
//		}
//		else{
//			pParse = pParse->m_pNext;
//		}
//	}
//
//	return pRet;
//}

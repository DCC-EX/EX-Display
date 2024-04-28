#include "EXDisplayRow.h"
/*
 * EXDisplayRow class implementation
 */
EXDisplayRow::EXDisplayRow(uint8_t rowNumber) {
  _rowNumber=rowNumber;
  _maxMalloc=0;
  _rowText=nullptr; 
}

uint8_t EXDisplayRow::getRowNumber() { return _rowNumber; }

void EXDisplayRow::setRowText(char *rowText) {
  // Note size limit is 254 chars but that is beyond
  // the capability of the caller anyway.  
  // Ignore change if text the same...   
  if (_rowText && strcmp(_rowText,rowText)==0) return;

  uint8_t bytesNeeded = strlen(rowText)+1;
  if (bytesNeeded > _maxMalloc || !_rowText) {
     // _rowText is not big enough so realloc() it.
     // Deliberately dont realloc() if its big enough to
     // avolid fragmentation caused by realloc freeing 
     // the tail which we will probabaly need later anyway. 
    _rowText=(char *)realloc(_rowText, bytesNeeded);
    _maxMalloc=bytesNeeded; 
  }
  strcpy(_rowText, rowText);
  _changed = true;
}

char *EXDisplayRow::getRowText() {
  _changed = false;  // are you sure... every time?
  return _rowText;
}

bool EXDisplayRow::isChanged() { return _changed; }


EXDisplayRow *EXDisplayRow::getNext() { return _next; }

void EXDisplayRow::setNext(EXDisplayRow *next) {_next=next;}

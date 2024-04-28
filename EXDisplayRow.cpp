#include "EXDisplayRow.h"
/*
 * EXDisplayRow class implementation
 */
EXDisplayRow::EXDisplayRow(uint8_t rowNumber) {
  _rowNumber=rowNumber;
  _rowText=nullptr; 
}

uint8_t EXDisplayRow::getRowNumber() { return _rowNumber; }

void EXDisplayRow::setRowText(char *rowText) {
  // ignore change if text the same...   
  if (_rowText && strcmp(_rowText,rowText)==0) return;

  uint8_t length = strlen(rowText);
  _rowText=(char *)realloc(_rowText, length + 1);
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

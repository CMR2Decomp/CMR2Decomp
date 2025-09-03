#include "RegKey.h"

#include <string.h>

// language related values
char CRegKey::m_regKeyLanguage[9] = "Language";
char CRegKey::m_regKeyValueAmerican[9] = "American";
char CRegKey::m_regKeyValuePolish[7] = "Polish";
char CRegKey::m_regKeyValueSpanish[8] = "Spanish";
char CRegKey::m_regKeyValueItalian[8] = "Italian";
char CRegKey::m_regKeyValueGerman[7] = "German";
char CRegKey::m_regKeyValueFrench[7] = "French";
char CRegKey::m_regKeyValueEnglish[8] = "English";

// sku related values
char CRegKey::m_regKeySkuType[9] = "Sku_Type";
char CRegKey::m_skuJapan[6] = "JAPAN";
char CRegKey::m_skuPoland[7] = "POLAND";
char CRegKey::m_skuAmerica[8] = "AMERICA";
char CRegKey::m_skuEurope[7] = "EUROPE";

// STUB: CMR2 0x004aa720
char *__stdcall CRegKey::GetValueFromKey(char *key)
{
    // TODO: make this better
    if (!strcmp(key, m_regKeySkuType))
        return m_skuEurope;

    return 0;
}

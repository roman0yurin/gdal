//
// Created by vitaliy on 5/12/21.
//

#ifndef ALTIUS_NATIVE_MAIN_H
#define ALTIUS_NATIVE_MAIN_H

/**
 * Структуры формата SXF
 *
 * sxfFile.
 *  OGRDataSource.
 *    GDALDataset.
 *      GDALMajorObject.
 *      m_poPrivate.
 *      oDerivedMetadataList.
 *      poDriver (NULL)
 *      eAccess (GDALAcces)
 *      nRasterXSize (int)
 *      nRasterYSize (int)
 *      nBands (int)
 *      papoBands (GDALRasterBand** | 0x0) NULL
 *      nOpenFlags (int)
 *      nRefCount (int)
 *      bForceCachedIO (bool)
 *      bShared (bool)
 *      bIsInternal (bool)
 *      bSuppressOnClose (bool)
 *      m_oMapFieldDomains.
 *      oOvManager.
 *      papszOpenOptions (char ** | 0x0) NULL
 *      m_poStyleTable (OGRStyleTable * | 0x0) NULL
 *
 *
 *  oSXFPassport.  -  Паспорт SXF файла
 *    version (GUInt32) (4)
 *    dtCrateDate.  -  Дата создания набора данных
 *      nYear (GUInt16) - год
 *      nMonth (GUInt16) - месяц
 *      nDay (GUInt16) - день
 *    sMapSheet.(string)    -  Номенклатура листа
 *    nScale (GUInt32)  - Масштаб листа
 *    sMapSheetName.(string) - Имя листа карты
 *    informationFlags.  -  Информационные флажки
 *      bProjectionDataCompliance (bool) - Соответствие проекционных данных ???
 *      bRealCoordinatesCompliance (bool) - Флаг наличия реальных координат
 *      stCodingType (SXFCodingType) (SXF_SEM_DEC) - Флаг способа кодирования 2 бита
 *      stGenType (SXFGeneralizationType) - Таблица генерализации 1 бит
 *      stEnc (SXFTextEncoding) SXF_ENC_WIN - Флаг кодировки текстов подписей объектов (1 байт)
 *      stCoordAcc (SXFCoordinatesAccuracy) - Флаг точности координат (1 байт):
 *      bSort (bool) - Признак специальной сортировки данных
 *    stMapDescription.  -  Описание карты ()
 *
 *  pszName.
 *    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >  --- Путь к файлу
 *
 *  papoLayers.
 *    *papoLayers.
 *      OGRLayer.
 *      poFeatureDefn.
 *      fpSXF.
 *      nLayerID (int)
 *      mnClassificators.
 *      mnRecordDesc.
 *      oNextIt.
 *      stSXFMapDescription.
 *      m_nSXFFormatVer (int)
 *      sFIDColumn_.
 *      m_hIOMutex.
 *      m_dfCoeff (double)
 *
 * Изменения в GDAL :
 *
 * - поле SXFPassport oSXFPassport - в классе OGRSXFDataSource перенесено в public
 *
 *
 */







#endif //ALTIUS_NATIVE_MAIN_H

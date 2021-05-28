//
// Created by vitaliy on 5/12/21.
//

#ifndef ALTIUS_NATIVE_MAIN_H
#define ALTIUS_NATIVE_MAIN_H


OGRSXFLayer::OGRSXFLayer(
        VSILFILE* fp, CPLMutex** hIOMutex, GByte nID, const char* pszLayerName,
        int nVer, const SXFMapDescription&  sxfMapDesc)
FILE VSILFILE

/**
 * VSILFILE* -
 */




/**
 * Структуры формата SXF
 *
 * sxfFile.
 *  OGRDataSource.
 *    GDALDataset.
 *      GDALMajorObject.  -  Главный объект GDAL
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
 *      bProjectionDataCompliance (bool) - Соответствие проекционных данных (флаг в описании - резерв)
 *      bRealCoordinatesCompliance (bool) - Флаг наличия реальных координат
 *      stCodingType (SXFCodingType) (SXF_SEM_DEC) - Флаг способа кодирования 2 бита
 *      stGenType (SXFGeneralizationType) - Таблица генерализации 1 бит
 *      stEnc (SXFTextEncoding) SXF_ENC_WIN - Флаг кодировки текстов подписей объектов (1 байт)
 *      stCoordAcc (SXFCoordinatesAccuracy) - Флаг точности координат (1 байт):
 *      bSort (bool) false - Признак специальной сортировки данных
 *    stMapDescription.  -  Описание карты ()
 *
 *  pszName.
 *    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >  --- Путь к файлу
 *
 *  papoLayers.
 *    *papoLayers.
 *      OGRLayer.
 *      poFeatureDefn.
 *        nRefCount (volatile int)
 *        nFieldCount (int)
 *        papoFieldDefn.
 *        nGeomFieldCount (int)
 *        papoGeomFieldDefn.
 *          pszName (char *). - string
 *          eGeomType (OGRwkbGeometryType) wkbUnknown
 *          poSRS (OGRSpatialReference).  -  Пространственная привязка
 *            d
 *              get()...
 *
 *          bIgnore (int)
 *          bNullable (int)
 *        pszFeatureClassName. (string) "SYSTEM"
 *        bIgnoreStyle (int)
 *      fpSXF.
 *      nLayerID (int)
 *      mnClassificators.
 *      mnRecordDesc.
 *      oNextIt.
 *      stSXFMapDescription.  -  Дескриптор SFX карты
 *        stProjCoords (double[8])  -  Прямоугольные координаты углов листа(паспорт)
 *        stGeoCoords (double[8]) - Геодезические координаты углов листа
 *        stFrameCoords (double[8]) - Расположение рамки на приборе
 *        Env. - крайние координаты углов
 *          MinX (double)
 *          MaxX (double)
 *          MinY (double)
 *          MaxY (double)
 *        pSpatRef.    -  пространственные Ссылки
 *        eUnitInPlan (SXFCoordinateMeasUnit) SXF_COORD_MU_METRE - единицы измерения - метры
 *        dfXOr (double)
 *        dfYOr (double)
 *        dfFalseNorthing (double)
 *        dfFalseEasting (double) - 500000 - масштаб?
 *        nResolution (GUInt32) - 500000 - масштаб?
 *        dfScale (double) - 500000 - масштаб
 *        bIsRealCoordinates (bool)
 *        stCoordAcc (SXFCoordinateAccuracy) SXF_COORD_ACC_HIGH - точность координат
 *      snAttributeCodes
 *      m_nSXFFormatVer (int)
 *      sFIDColumn_.
 *      m_hIOMutex.
 *      m_dfCoeff (double)
 *
 * Изменения в GDAL :
 *
 * - поле SXFPassport oSXFPassport - в классе OGRSXFDataSource перенесено в public
 * - поле OGRLayer**  papoLayers  - в классе OGRSXFDataSource перенесено в public
 *
 *
 */







#endif //ALTIUS_NATIVE_MAIN_H

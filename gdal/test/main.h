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
 *      
 *
 *
 *  oSXFPassport.  -  Паспорт SXF файла
 *    dtCrateDate.  -  Дата создания набора данных
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

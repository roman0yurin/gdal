//
// Created by vitaliy on 5/3/21.
//



#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>

#include "helloWorld.h"

#include <sxf/ogr_sxf.h>

//#include "../../gdal/ogr/ogrsf_frmts/pgeo/ogrpgeolayer.cpp"



using namespace std;


int main( int argc, char* argv[] ){
    fprintf(stdout, "Hello Gdal\n");

    /** объект класса */
    OGRSXFDataSource sxfFile;
    /** Путь к файлу */
//    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/K371.sxf";
    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/K362.sxf";
//    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/K372.sxf";
//    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/L364.sxf";
//    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/L362.sxf";
    /** Открываем файл */
    sxfFile.Open(path,0,0);

    /** Количество слоёв */
    cout << "Количество слоёв:  " << sxfFile.GetLayerCount() << "\n";
    int quaLayer = sxfFile.GetLayerCount();

    /** Структуры для чтения слоя */
    OGRLayer* sxfLayer;



    /** Цикл по слоям */
    for(int  i = 0; i < quaLayer; i++){
        /** Читаем слой */
        sxfLayer = sxfFile.GetLayer(i);
        /** Стартуем итератор - чтение данных (OGRFeature*) открытого листа карты */
        auto iter = sxfLayer->begin();

        /** Счётчик записей */
        GIntBig RecordsCount = sxfLayer->GetFeatureCount();


        cout << "======================================================================================\n";
        cout << "=========================   СЛОЙ: " << i << "  " << sxfLayer->GetName() << "    =======================================\n";
        cout << "======================================================================================\n";
        cout << i <<" Записей в слое: " << RecordsCount << "\n";

        /** Цикл по записям (Feature) слоя */
        for(int i = 0; i < RecordsCount; i++) {

            /** Количество полей в записи */
            int fieldCount = (*iter)->GetFieldCount();

            /** Итератор по полям записи */
            auto fieldIter = (*iter)->begin();

            cout << i <<" fieldCount: " << fieldCount << "\n";

            /** Цикл по полям записи */
            for(int i = 0; i < fieldCount; i++){

                cout << "| " << i <<" Name: " << (*fieldIter).GetName() << "; ";
//                cout << " " << "  type: " << (*fieldIter).GetType() << ";  ";

                /** topic Стиль элемента ??? */
//                auto type = styleTable->;

                /** Проверка типа данных в поле */
                int typeField = (*fieldIter).GetType();
                switch (typeField) {

                    case OFTInteger: {
                        cout << " Int: " << (*fieldIter).GetAsInteger() << " ";
                        break;
                    }
                    case OFTReal: {
                        cout << " Float: " << (*fieldIter).GetAsDouble() << " ";
                        break;
                    }
                    case OFTString: {
                        cout << " String: " << (*fieldIter).GetAsString() << " ";
                        break;
                    }
                    default: {
                        cout << "  ??? UnsignedType " ;
                    }
                }
                fieldIter.operator++();
            }


            /** Геометрия */
            auto ref = (*iter)->GetGeometryRef()->toLineString();
            (*iter)->GetGeomFieldCount();
            (*iter)->GetGeomFieldIndex("");
            (*iter)->GetGeomFieldRef(1); //

            cout << "\n";

            /** Ссылка на геометрию  */
            OGRGeometry* geom = (*iter)->GetGeometryRef();


            /** Тип геометрии в виде 1001, 1002, 1004, 1005 */
            auto wathType = (*iter)->StealGeometry()  ;
            cout << " |" <<" wathType: " << wathType->getIsoGeometryType() << "\n   ";


            cout << " |" <<" GetGeometryRef(): " << (*iter)->GetGeometryRef() << "   ";
            /** количество полей геометрии */
            cout << " |" <<" GetGeomFieldCount(): " << (*iter)->GetGeomFieldCount() << "   ";
            /** Имя геометрии */
            cout << " |" <<" getGeometryName(): " << geom->getGeometryName() << "  ";

            /** Тип геометрии */
            auto geomType = geom->getGeometryType();

            string a;
            switch (geomType) {
                case wkbPoint25D:{a = "wkbPoint25D"; break;}
                case wkbLineString25D:{a = "wkbLineString25D"; break;}
                case wkbPolygon25D:{a = "wkbPolygon25D"; break;}
                case wkbMultiPoint25D:{a = "wkbMultiPoint25D"; break;}
                case wkbMultiLineString25D:{a = "wkbMultiLineString25D"; break;}
                case wkbMultiPolygon25D:{a = "wkbMultiPolygon25D"; break;}
                case wkbGeometryCollection25D:{a = "wkbGeometryCollection25D"; break;}
                default:{a="UnknownType"; break;}
            }
            cout << " |" <<" GeometryType: " << a << "\n  ";

            cout << " |" <<" geom->WkbSize() " << geom->WkbSize() << "\n  ";
            cout << " |" <<" geom->getDimension() " << geom->getDimension() << "\n  ";
            cout << " |" <<" exportToKML(): " << geom->exportToKML() << "\n  ";

            /** topic Стиль элемента ??? */

            iter.operator++();

            cout << "\n";
        }

        cout << "\n";

    }


    /** Файл - характеристики */
    cout << "Файл :  " << path << "\n";

    int a = sxfFile.GetLayerCount();
    cout << "Количество слоёв:  " << a << "\n";

    string fileName = sxfFile.GetName();
    cout << "Имя файла: " << fileName << "\n";

    string b = sxfFile.GetDescription();
    cout << "Description: " << b << "\n";

    /** Дата создания файла */
//    int Year = sxfFile.oSXFPassport.dtCrateDate.nYear;
//    int month = sxfFile.oSXFPassport.dtCrateDate.nMonth;
//    int day = sxfFile.oSXFPassport.dtCrateDate.nDay;
//    cout << "Дата создания файла: " << day << "." << month << "." << Year << "\n";

    /** Масштаб листа */
//    int scale = sxfFile.oSXFPassport.nScale;
//    cout << "Масштаб листа:  1:" << scale << "\n";

    /** Имя листа карты */
//    string mapSheetName = sxfFile.oSXFPassport.sMapSheetName;
//    cout << "Имя листа карты: " << mapSheetName << "\n";

    /** Номенклатура листа */
//    string mapSheet = sxfFile.oSXFPassport.sMapSheet;
//    cout << "Номенклатура листа: " << mapSheet << "\n";




    cout << "SummaryRefCount: " << sxfFile.GetSummaryRefCount() << "\n"; // Чтение счётчика ссылок набора данных

    sxfFile.GetFileList(); // Возвращает список файлов, которые считаются частью этого набора данных

    /** -------------------------------------------------------------- */
    sxfFile.GetLayerByName(""); // Получить слой по имени.

    /** -------------------------------------------------------------- */

    sxfFile.CloseFile()  ;  // Закрываем файл


    testHelloWorld();


    return 0;
}




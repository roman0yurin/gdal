//
// Created by vitaliy on 5/3/21.
//



#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>



#include "sxf/ogr_sxf.h"




//#include "../../gdal/ogr/ogrsf_frmts/pgeo/ogrpgeolayer.cpp"



using namespace std;


int main( int argc, char* argv[] ){
    fprintf(stdout, "Hello Gdal\n");

    /** объект класса */
    OGRSXFDataSource sxfFile;
    /** Путь к файлу */
    char path[] = "";
//    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/K362.sxf";
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
        /** Стартуем итератор по записям слоя - чтение данных (OGRFeature*) */
        auto fIter = sxfLayer->begin();

        /** Счётчик записей */
        GIntBig RecordsCount = sxfLayer->GetFeatureCount();


        cout << "======================================================================================\n";
        cout << "=========================   СЛОЙ: " << i << "  " << sxfLayer->GetName() << "    =======================================\n";
        cout << "======================================================================================\n";
        cout << i <<" Записей в слое: " << RecordsCount << "\n";

        /** Цикл по записям (Feature) слоя */
        for(int i = 0; i < RecordsCount; i++) {

            /** Количество полей в записи */
            int fieldCount = (*fIter)->GetFieldCount();

            /** Итератор по полям записи */
            auto fieldIter = (*fIter)->begin();

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
            auto ref = (*fIter)->GetGeometryRef()->toLineString();
            (*fIter)->GetGeomFieldCount();
            (*fIter)->GetGeomFieldIndex("");
            (*fIter)->GetGeomFieldRef(1); //

            cout << "\n";

            /** Ссылка на геометрию  */
            OGRGeometry* geomRef = (*fIter)->GetGeometryRef();

            /** Размер геометрии в WKB формате */
            auto wkbSize = geomRef->WkbSize();
            cout << "\n |" <<" wkbSize: " << to_string(wkbSize) << "\n   ";

            /** Тип геометрии в виде 1001, 1002, 1004, 1005 */
            auto wathType = (*fIter)->StealGeometry()  ;
            cout << " |" <<" wathType: " << wathType->getIsoGeometryType() << "\n   ";


            cout << " |" << " GetGeometryRef(): " << (*fIter)->GetGeometryRef() << "   ";
            /** количество полей геометрии */
            cout << " |" << " GetGeomFieldCount(): " << (*fIter)->GetGeomFieldCount() << "   ";
            /** Имя геометрии */
            cout << " |" << " getGeometryName(): " << geomRef->getGeometryName() << "  ";

            /** Тип геометрии */
            auto geomType = geomRef->getGeometryType();

            /** Указатель на размещение поля геометрии */
            OGRGeometry* geomFieldRef = (*fIter)->GetGeomFieldRef(0);

            /** Селектор по типу геометрии */
            string a;
            switch (geomType) {
                case wkbPoint25D:{
                    a = "wkbPoint25D";

                    cout << "\n |" << " getM: " << to_string(geomRef->toPoint()->getM()) << "\n  ";
                    cout << " |" << " getX: " << to_string(geomRef->toPoint()->getX()) << "\n  ";
                    cout << " |" << " getY: " << to_string(geomRef->toPoint()->getY()) << "\n  ";
                    cout << " |" << " getZ: " << to_string(geomRef->toPoint()->getZ()) << "\n  ";
                    break;
                }
                case wkbLineString25D:{
                    a = "wkbLineString25D";
                    cout << "\n |" << " NumPoints: " << to_string(geomRef->toLineString()->getNumPoints()) << "\n  ";
                    cout << " |" << " GeometryName: " << geomRef->toLineString()->getGeometryName() << "\n  ";

                    /** Цикл(итератор) по точкам линии */
                    for(auto pointIter = geomRef->toLineString()->begin();
                            pointIter != geomRef->toLineString()->end(); ++pointIter){
                        cout << " |" <<" getM: " << to_string((*pointIter).getM()) << "\n  ";
                        cout << " |" <<" getX: " << to_string((*pointIter).getX()) << "\n  ";
                        cout << " |" <<" getY: " << to_string((*pointIter).getY()) << "\n  ";
                        cout << " |" <<" getZ: " << to_string((*pointIter).getZ()) << "\n  ";
                    }
                    break;
                }
                case wkbPolygon25D:{
                    a = "wkbPolygon25D";

                    /** количество встроенных полигонов, ноль или больше. */
                    int numInteriorRings = geomRef->toPolygon()->getNumInteriorRings();
                    cout << "\n |" << " Встроено : " << numInteriorRings << "\n  ";

                    /** итератор по полям геометрии  полигона */
                    int numIter = 0;
                    for(auto poligonIter = geomRef->toPolygon()->begin(); poligonIter != geomRef->toPolygon()->end(); ++poligonIter){

                        cout << "|" << " numInter : " << numIter << "\n  ";

                        /** тип геометрии поля полигона */
                        cout << "|" << " inputGeometryType : " << (*poligonIter)->getGeometryType() << "\n  ";
                        int poligonFieldType = (*poligonIter)->getGeometryType();
                        cout << "|" << " inputGeometryType : " << OGRGeometryTypeToName((*poligonIter)->getGeometryType()) << "\n  ";

                        /** Длина линии полигона */
                        cout << "|" << " Length : " << to_string((*poligonIter)->get_Length()) << "\n  ";

                        /** Простой контейнер для ограничивающей области (прямоугольник) (*poligonIter)->getEnvelope(); */
                        /** Возвращает TRUE, если кривая замкнута (*poligonIter)->get_IsClosed() */


                        /** количество точек */
                        (*poligonIter)->getNumPoints();
                        cout << "|" << " точек : " << (*poligonIter)->getNumPoints() << "\n  ";

                        /**  Цикл по точкам координат  */
                        int pNum = 0;
                        for(auto pointIter = (*poligonIter)->begin(); pointIter != (*poligonIter)->end(); ++pointIter){
                            cout << " |" <<" pNum: " << pNum << "\n  ";
                            cout << " |" <<" getM: " << to_string((*pointIter).getM()) << "\n  ";
                            cout << " |" <<" getX: " << to_string((*pointIter).getX()) << "\n  ";
                            cout << " |" <<" getY: " << to_string((*pointIter).getY()) << "\n  ";
                            cout << " |" <<" getZ: " << to_string((*pointIter).getZ()) << "\n  ";
                            pNum++;
                        }

                    }

                    break;
                }
                case wkbMultiPoint25D:{
                    a = "wkbMultiPoint25D";
                    int mPointCount = geomRef->toMultiPoint()->getNumGeometries();
                    cout << "\n|" << " точек : " << mPointCount << "\n  ";

                    int pNum = 0;

                    /** Цикл по полям multiPoint */
                    for(auto pointIter = geomRef->toMultiPoint()->begin();
                            pointIter != geomRef->toMultiPoint()->end(); ++pointIter){
                        cout << " |" <<" pNum: " << pNum << "\n  ";
                        cout << " |" <<" getM: " << to_string((*pointIter)->getM()) << "\n  ";
                        cout << " |" <<" getX: " << to_string((*pointIter)->getX()) << "\n  ";
                        cout << " |" <<" getY: " << to_string((*pointIter)->getY()) << "\n  ";
                        cout << " |" <<" getZ: " << to_string((*pointIter)->getZ()) << "\n  ";
                        pNum++;
                    }



                    break;
                }
                case wkbMultiLineString25D:{
                    a = "wkbMultiLineString25D";

                    /** Длина мультилинии */
                    cout << "\n |" << " Length: " << to_string(geomRef->toMultiLineString()->get_Length()) << "\n  ";

                    cout << " |" << " GeometryName: " << geomRef->toMultiLineString()->getGeometryName() << "\n  ";
                    cout << " |" << " NumGeometries: " << geomRef->toMultiLineString()->getNumGeometries() << "\n  ";

                    /** Итератор по полям геометрии MultiLineString */
                    for(auto gIter = geomRef->toMultiLineString()->begin(); gIter != geomRef->toMultiLineString()->end(); ++gIter){

                        /** Количество точек линии */
                        int pointCount = (*gIter)->getNumPoints();
                        cout << "\n |" << " NumPoints: " << pointCount << "\n  ";

                        int pNum = 0; // номер точки
                        /** Цикл по точкам координат */
                        for(auto pointIter = (*gIter)->begin(); pointIter != (*gIter)->end(); ++pointIter){
                            cout << " |" <<" pNum: " << pNum << "\n  ";
                            cout << " |" <<" getM: " << to_string((*pointIter).getM()) << "\n  ";
                            cout << " |" <<" getX: " << to_string((*pointIter).getX()) << "\n  ";
                            cout << " |" <<" getY: " << to_string((*pointIter).getY()) << "\n  ";
                            cout << " |" <<" getZ: " << to_string((*pointIter).getZ()) << "\n  ";
                            pNum++;
                        }

                        /** Площадь замкнутая кривой */
                        double area = (*gIter)->get_Area();

                        /** Получить размерность координат в этом объекте. Вернет 2 или 3. */
                        int coordinateDimension = (*gIter)->getCoordinateDimension();

                    }

                    break;
                }
                case wkbMultiPolygon25D:{a = "wkbMultiPolygon25D"; break;}
                case wkbGeometryCollection25D:{a = "wkbGeometryCollection25D"; break;}
                default:{a="UnknownType"; break;}
            }
            cout << " |" <<" GeometryType: " << a << "\n  ";

            cout << " |" << " geomRef->WkbSize() " << geomRef->WkbSize() << "\n  ";
            cout << " |" << " geomRef->getDimension() " << geomRef->getDimension() << "\n  ";
            cout << " |" << " exportToKML(): " << geomRef->exportToKML() << "\n  ";

            /** Проверяет, находится ли геометрический объект в пределах переданной геометрии
            * @param poOtherGeom - геометрия для сравнения с этой геометрией */
//            geomRef->Within(0);

            /** Поиск поля геометрии по имени */
//            int geomFieldIndex = (*fIter)->GetGeomFieldIndex(0);

            /** вернуть тип геометрии, соответствующий ISO SQL / MM Part3 */
//            int isoSqlType = geomFieldRef->getIsoGeometryType();




            /** topic Стиль элемента ??? */
//            (*fIter)->GetStyleTable();
//            (*fIter)->GetStyleString();
//            /** Получить название стиля по строке стиля */
//            (*fIter)->GetStyleTable()->GetStyleName("0");
//            /** Получить следующую строку стиля из таблицы */
//            (*fIter)->GetStyleTable()->GetNextStyle();
//            /** Получить имя стиля последней строки стиля, полученной с помощью OGR_STBL_GetNextStyle */
//            (*fIter)->GetStyleTable()->GetLastStyleName();


            ++fIter; // итератор по записям слоя

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





    return 0;
}




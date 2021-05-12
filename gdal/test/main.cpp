//
// Created by vitaliy on 5/3/21.
//



#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>


#include </home/vitaliy/develop/work/altius_gdal/ext_lib/gdal/gdal/ogr/ogrsf_frmts/sxf/ogr_sxf.h>



using namespace std;


int main( int argc, char* argv[] ){
    fprintf(stdout, "Hello Gdal\n");

    /**
     * Открытие файла SXF Panorama
     */
//    ifstream sxfFile("/home/vitaliy/develop/GDAL_Panorama/Maps/K371.sxf");
//    if(!sxfFile) {
//        cout << "Не удалось открыть файл.\n";
//    }
//    else cout << "Файл открыт.\n";


    OGRSXFDataSource sxfFile;
    /** Путь к файлу */
    char path[] = "/home/vitaliy/develop/GDAL_Panorama/Maps/K371.sxf";
    sxfFile.Open(path,0,0);



    cout << "Файл :  " << path << "\n";

    int a = sxfFile.GetLayerCount();
    cout << "Количество слоёв:  " << a << "\n";

    string fileName = sxfFile.GetName();
    cout << "Имя файла: " << fileName << "\n";

    string b = sxfFile.GetDescription();
    cout << "Description: " << b << "\n";

    /** Дата создания файла */
    int Year = sxfFile.oSXFPassport.dtCrateDate.nYear;
    int month = sxfFile.oSXFPassport.dtCrateDate.nMonth;
    int day = sxfFile.oSXFPassport.dtCrateDate.nDay;
    cout << "Дата создания файла: " << day << "." << month << "." << Year << "\n";

    /** Масштаб листа */
    int scale = sxfFile.oSXFPassport.nScale;
    cout << "Масштаб листа:  1:" << scale << "\n";


    //int opt = sxfFile.Reference() ; // Увеличение счётчика ссылок набора данных на 1

    int SummaryRefCount = sxfFile.GetSummaryRefCount();
    cout << "SummaryRefCount: " << SummaryRefCount << "\n"; // Чтение счётчика ссылок набора данных

    //sxfFile.BuildParseInfo(); // Полуобщественные методы. Только для использования драйверами в дереве.
    //sxfFile.GetInternalHandle(); // Класс, возвращаемый GetBands (), который действует как контейнер для растровых каналов.
    sxfFile.GetFileList(); // Возвращает список файлов, которые считаются частью этого набора данных

    /** -------------------------------------------------------------- */
    sxfFile.GetLayerByName(""); // Получить слой по имени.

    /** -------------------------------------------------------------- */

    sxfFile.CloseFile()  ;  // Закрываем файл
    return 0;
}

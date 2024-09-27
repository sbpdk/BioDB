// DB_Bio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tuple>
#include <memory>
#include <iomanip>
#include <iostream>
#include "Database.h"
#include "Create.h"
#include "SqliteDB.h"
#include "BiomassPipeRun.h"
#include "PipeRunBiomass.h"
#include "EXCEL.h"

using namespace std;

void CreateDB()
{
    Create create;
    create.BioDB2();
}



void InsertTubes()
{
    DATABASE::SqliteDB sql("BioDB.db");
    
    vector<tuple<string, string, int, double, double>> vec = {
        make_tuple("C1_15", "C1", 15, 21.3, 2.0),
        make_tuple("C1_20", "C1", 20, 26.9, 2.3),
        make_tuple("C1_25", "C1", 25, 33.7, 2.6),
        make_tuple("C1_32", "C1", 32, 42.2, 2.6),
        make_tuple("C1_40", "C1", 40, 48.3, 2.6),
        make_tuple("C1_50", "C1", 50, 60.3, 2.9),
        make_tuple("C1_65", "C1", 65, 76.1, 2.9),
        make_tuple("C1_80", "C1", 80, 88.9, 3.2),
        make_tuple("C1_100", "C1", 100, 114.3, 3.6),
        make_tuple("C1_125", "C1", 125, 139.7, 4.0),
        make_tuple("C1_150", "C1", 150, 168.3, 4.5),
        make_tuple("C1_200", "C1", 200, 219.1, 6.3),
        make_tuple("C1_250", "C1", 250, 273.0, 6.3),
        make_tuple("C1_300", "C1", 300, 323.9, 7.1),
        make_tuple("C1_350", "C1", 350, 356.6, 8.0),
        make_tuple("C1_400", "C1", 400, 406.7, 8.8)       
    };

    int err = 0;
    for (tuple<string, string, int, double, double> ror : vec)
    {
        err = sql.InsertRor(std::get<0>(ror), std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "C2_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, "C2", std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "C3_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, "C3", std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "C4_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, "C4", std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "C5_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, "C5", std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "C6_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, "C6", std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
}


void InsertTubes2()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<tuple<string, string, int, double, double>> vec = {
        make_tuple("P1_20", "P1", 20, 20.0, 2.0),
        make_tuple("P1_25", "P1", 25, 25.0, 2.3),
        make_tuple("P1_32", "P1", 32, 32.0, 2.9),
        make_tuple("P1_40", "P1", 40, 40.0, 2.4),
        make_tuple("P1_50", "P1", 50, 50.0, 3.0),
        make_tuple("P1_65", "P1", 63, 63.0, 3.8),
        make_tuple("P1_75", "P1", 75, 75.0, 4.5),
        make_tuple("P1_90", "P1", 90, 90.0, 5.4),
        make_tuple("P1_110", "P1", 110, 110.0, 6.6),
        make_tuple("P1_125", "P1", 125, 125.0, 7.4),
        make_tuple("P1_140", "P1", 140, 140.0, 8.3),
        make_tuple("P1_160", "P1", 160, 160.0, 9.5),
        make_tuple("P1_180", "P1", 180, 180.0, 10.7),
        make_tuple("P1_200", "P1", 200, 200.0, 11.9),
        make_tuple("P1_225", "P1", 225, 225.0, 13.4),
        make_tuple("P1_250", "P1", 250, 250.0, 14.8),
        make_tuple("P1_280", "P1", 280, 280.0, 16.6),
        make_tuple("P1_315", "P1", 315, 315.0, 18.7),
        make_tuple("P1_355", "P1", 355, 355.0, 21.1),
        make_tuple("P1_400", "P1", 400, 400.0, 23.7),
        make_tuple("P1_450", "P1", 450, 450.0, 26.7),
        make_tuple("P1_500", "P1", 500, 500.0, 29.7),
        make_tuple("P1_560", "P1", 560, 560.0, 33.2),
        make_tuple("P1_630", "P1", 630, 630.0, 37.4)
    };

    int err = 0;
    for (tuple<string, string, int, double, double> ror : vec)
    {
        err = sql.InsertRor(std::get<0>(ror), std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
    for (tuple<string, string, int, double, double> ror : vec)
    {
        string pk = "P3_" + to_string(std::get<2>(ror));
        err = sql.InsertRor(pk, std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
}



void InsertTubes3()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<tuple<string, string, int, double, double>> vec = {
        make_tuple("P2_40", "P2", 40, 40.0, 3.7),
        make_tuple("P2_50", "P2", 50, 50.0, 4.6),
        make_tuple("P2_63", "P2", 63, 63.0, 3.8),
        make_tuple("P2_75", "P2", 75, 75.0, 4.5),
        make_tuple("P2_90", "P2", 90, 90.0, 5.4),
        make_tuple("P2_110", "P2", 110, 110.0, 6.6),
        make_tuple("P2_125", "P2", 125, 125.0, 7.4),
        make_tuple("P2_140", "P2", 140, 140.0, 8.3),
        make_tuple("P2_160", "P2", 160, 160.0, 9.5),
        make_tuple("P2_180", "P2", 180, 180.0, 10.7),
        make_tuple("P2_200", "P2", 200, 200.0, 11.9),
        make_tuple("P2_225", "P2", 225, 225.0, 13.4)        
    };

    int err = 0;
    for (tuple<string, string, int, double, double> ror : vec)
    {
        err = sql.InsertRor(std::get<0>(ror), std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };   
}


void InsertTubes4()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<tuple<string, string, int, double, double>> vec = {
        make_tuple("P4_63", "P4", 63, 63.0, 3.8),
        make_tuple("P4_75", "P4", 75, 75.0, 4.5),
        make_tuple("P4_90", "P4", 90, 90.0, 5.4),
        make_tuple("P4_110", "P4", 110, 110.0, 6.6),
        make_tuple("P4_125", "P4", 125, 125.0, 7.4),
        make_tuple("P4_140", "P4", 140, 140.0, 8.3),
        make_tuple("P4_160", "P4", 160, 160.0, 9.5),
        make_tuple("P4_180", "P4", 180, 180.0, 10.7),
        make_tuple("P4_200", "P4", 200, 200.0, 11.9),
        make_tuple("P4_225", "P4", 225, 225.0, 13.4),
        make_tuple("P4_250", "P4", 250, 250.0, 14.8),
        make_tuple("P4_280", "P4", 280, 280.0, 16.6),
        make_tuple("P4_315", "P4", 315, 315.0, 18.7),
        make_tuple("P4_355", "P4", 355, 355.0, 21.1),
        make_tuple("P4_400", "P4", 400, 400.0, 23.7)       
    };

    int err = 0;
    for (tuple<string, string, int, double, double> ror : vec)
    {
        err = sql.InsertRor(std::get<0>(ror), std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
}



void InsertTubes5()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<tuple<string, string, int, double, double>> vec = {
        make_tuple("S4_15", "S4", 15, 21.3, 2.0),
        make_tuple("S4_20", "S4", 20, 26.9, 2.0),
        make_tuple("S4_25", "S4", 25, 33.7, 2.0),
        make_tuple("S4_32", "S4", 32, 42.2, 2.0),
        make_tuple("S4_40", "S4", 40, 48.3, 2.0),
        make_tuple("S4_50", "S4", 50, 60.3, 2.0),
        make_tuple("S4_65", "S4", 65, 76.1, 2.0),
        make_tuple("S4_80", "S4", 80, 88.9, 2.0),
        make_tuple("S4_100", "S4", 100, 114.3, 2.0),
        make_tuple("S4_150", "S4", 150, 168.3, 2.0),
        make_tuple("S4_200", "S4", 200, 219.1, 2.0),
        make_tuple("S4_250", "S4", 250, 273.0, 2.0),
        make_tuple("S4_300", "S4", 300, 323.9, 3.0),
        make_tuple("S4_350", "S4", 350, 356.6, 3.0),
        make_tuple("S4_400", "S4", 400, 406.7, 3.0)       
    };

    int err = 0;
    for (tuple<string, string, int, double, double> ror : vec)
    {
        err = sql.InsertRor(std::get<0>(ror), std::get<1>(ror), std::get<2>(ror), std::get<3>(ror), std::get<4>(ror));
        if (err != 0)
            cout << "Error" << endl;
        else
            cout << std::get<0>(ror) << " " << std::get<1>(ror) << "  Ok" << endl;
    };
}


//Projekt Specifikke いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
void CreatProject()
{
    DATABASE::SqliteDB sql("BioDB.db");

    sql.InsertProject("Project Upgrade");
}
//BiomassPipeRun(std::string name, std::shared_ptr<CIRCUIT::BiomassCmp> bioCmps, double inletHead_m, double outletHead_m);

/*Insert piperuns*/
void InsertPipeRuns()
{
    vector<shared_ptr<PLANT::BiomassPipeRun>> vec = {
        make_shared<PLANT::BiomassPipeRun>("Pre Buffer Tank to Pre Tank Liquid Biomass", nullptr, 0.5, 6.0),
        make_shared<PLANT::BiomassPipeRun>("Pre Tank Liquid Biomass to PD", nullptr, 0.5, 22.0),
        make_shared<PLANT::BiomassPipeRun>("PD to SD", nullptr, 18.0, 22.0),
        make_shared<PLANT::BiomassPipeRun>("SD to Separation Buffer", nullptr, 18.0, 6.0),
        make_shared<PLANT::BiomassPipeRun>("Separation Buffer to Screw Buffer", nullptr, 6.0, 2.0),
        make_shared<PLANT::BiomassPipeRun>("Screw Buffer to End Storage", nullptr, 2.0, 6.0),
        make_shared<PLANT::BiomassPipeRun>("End Storage to Post Buffer", nullptr, 6.0, 4.0),
        make_shared<PLANT::BiomassPipeRun>("PD to Pre Mix", nullptr, 22.0, 22.0),
        make_shared<PLANT::BiomassPipeRun>("PD to Dusty Biomass", nullptr, 22.0, 22.0),
        make_shared<PLANT::BiomassPipeRun>("Pre Tank Heated to PD", nullptr, 5.0, 22.0),
        make_shared<PLANT::BiomassPipeRun>("Pre Tank Industrial Waste to Flex Feed", nullptr, 0.5, 5.0),
        make_shared<PLANT::BiomassPipeRun>("Flex Feed to PD", nullptr, 0.5, 22.0),
        make_shared<PLANT::BiomassPipeRun>("Recirculation BioWater Hex", nullptr, 0.0, 0.0)
    };

    DATABASE::SqliteDB sql("BioDB.db");
    int err = 0;
    for (shared_ptr<PLANT::BiomassPipeRun> pR : vec)
    {
        err = sql.InsertPipeRun("Project Upgrade", pR);
        if (err != 0)
            cout << "Error:  " << pR->GetName() << endl;
        else
            cout << "OK  " << pR->GetName() << endl;
    }
}


void LookAtDB()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<pair<string, string>> pipeRuns = sql.GetPipeRunNames("Project Upgrade");

    for (pair<string, string> res : pipeRuns)
        cout << res.first << "  " << res.second << endl;

   /* vector<string> pipeRuns = sql.GetRuns();
    for (string st : pipeRuns)
        cout << st << endl;*/
}

void TestRorPK()
{
    DATABASE::SqliteDB sql("BioDB.db");
    pair<string, int> res = sql.GetRor("P4_200");
    cout << res.first << "   " << res.second << endl;
}


void ReadData()
{
    EXCEL excel(false);
    vector<vector<string>> vec = excel.Get("C:\\test\\ProjectUprade_biomass.xlsx", 1, 400, 6);
    excel.Close();
   
    DATABASE::SqliteDB sql("BioDB.db");
    vector<pair<string, string>> pipeRuns = sql.GetPipeRunNames("Project Upgrade");
        
    int index = 0;
    int count = 0;
    string pipeRunName;
    string pk_ror = "";
    string inletPipe = "";
    string outletPipe = "";
    string pk = "";
    string tag = "";
    string ror = "";
    int dim = 0;
    double ruhed = 0.05e-3;
    bool skipHeader = false;
    int err = 0;
    int count2 = 0;
    shared_ptr<CIRCUIT::BiomassCmp> cmp = nullptr;
    for (vector<string> vv : vec)
    {
        if (skipHeader == true)
        {
            skipHeader = false;
            continue;
        }
        if (vv.at(0).compare("Z") == 0)
        {
            pipeRunName = pipeRuns.at(index).first;
            skipHeader = true;
            continue;
        }
        if (vv.at(0).compare("ZZ") == 0)
        {
            index++;
            //break;
            count = 0;
            continue;
        }
        if (vv.at(0).compare(" ") == 0)
            continue;
        count++;
        
        pk = pipeRunName + to_string(count);
        tag = vv.at(0);
        

        if (vv.at(1).compare("Pump") == 0)
            cmp = make_shared<CIRCUIT::BioPump>(tag, vv.at(2), nullptr);  
        else if (vv.at(1).compare("Macerator") == 0)
            cmp = make_shared<CIRCUIT::Macerator>(tag, vv.at(2), nullptr);
        else if (vv.at(1).compare("HEX") == 0)
            cmp = make_shared<CIRCUIT::BioHEX>(tag, vv.at(2), nullptr);
        else if (vv.at(1).compare("FlowMeter") == 0)
            cmp = make_shared<CIRCUIT::BioFlowMeter>(tag, vv.at(2), nullptr);
        else if (vv.at(1).compare("Screw Press") == 0)
            cmp = make_shared<CIRCUIT::BioFlowMeter>(tag, vv.at(2), nullptr);
        else if (vv.at(1).compare("Mixing chamber") == 0)
            cmp = make_shared<CIRCUIT::BioFlowMeter>(tag, vv.at(2), nullptr);
        else
        {
            dim = atoi(vv.at(2).c_str());
            cmp = make_shared<CIRCUIT::PipeRunBiomass>(tag, vv.at(1), dim, ruhed, 25.0, 5, 5, 0, 0, nullptr);
        }
      
        err = sql.InsertBioCmp(cmp, "Project Upgrade", pipeRunName);
        if (err == 0)
            cout << count2 << "  OK    " << vv.at(0) << endl;
        else
            cout << count2 << "  ERROR at   " << vv.at(0) << endl;
        count2++;
        //break;
    }
    
   
  
    int vv = 0;
}

void AddTable()
{
    Create create;
    create.AddTable();
}


void GetPipeRun()
{
    DATABASE::SqliteDB sql("BioDB.db");

    vector<pair<string, string>> pipeRuns = sql.GetPipeRunNames("Project Upgrade");
   
    shared_ptr<CIRCUIT::BiomassCmp> cmp = sql.GetBioCmps(pipeRuns.at(0).first);
   
   // sql.GetBioCmps();
}


void SetReferences()
{
    DATABASE::SqliteDB sql("BioDB.db");
    vector<pair<string, string>> pipeRuns = sql.GetPipeRunNames("Project Upgrade");

    for (pair<string, string> pipeRun : pipeRuns)
    {
        vector<shared_ptr<CIRCUIT::BiomassCmp>> cmps = sql.GetBioCmps2(pipeRun.first);

        for (unsigned int ii = 0; ii < cmps.size(); ii++)
        {
            if (ii == 0)
                sql.UpdateBioCmpRef("Project Upgrade", cmps.at(ii), nullptr, cmps.at(ii + 1));
            else if (ii == cmps.size() - 1)
                sql.UpdateBioCmpRef("Project Upgrade", cmps.at(ii), cmps.at(ii - 1), nullptr);
            else
                sql.UpdateBioCmpRef("Project Upgrade", cmps.at(ii), cmps.at(ii - 1), cmps.at(ii + 1));

        }
    }
}

void WriteReferences()
{
    DATABASE::SqliteDB sql("BioDB.db");
    vector<pair<string, string>> pipeRuns = sql.GetPipeRunNames("Project Upgrade");
    vector<shared_ptr<CIRCUIT::BiomassCmp>> cmps = sql.GetBioCmps2(pipeRuns.at(1).first);

    for (shared_ptr<CIRCUIT::BiomassCmp> cmp : cmps)
    {
        cout << left << setw(20) << cmp->GetTag() << setw(20) << cmp->GetUpStream()->GetTag() << setw(20) << cmp->GetDownStream()->GetTag() << endl;      
    }
        
}

void GetCompleteProject()
{
    DATABASE::SqliteDB sql("BioDB.db");
    vector<shared_ptr<PLANT::BiomassPipeRun>> runs = sql.GetBiomassPipeRuns("Project Upgrade");
    int vv = 0;
}


void UpDatePipeInPipeRun()
{
    DATABASE::SqliteDB sql("BioDB.db");
    vector<shared_ptr<PLANT::BiomassPipeRun>> runs = sql.GetBiomassPipeRuns("Project Upgrade");
    shared_ptr<CIRCUIT::BiomassCmp> cmp = runs.at(0)->GetBioComponents();
    shared_ptr<CIRCUIT::PipeRunBiomass> pR = dynamic_pointer_cast<CIRCUIT::PipeRunBiomass>(cmp);
    cout << pR->GetLength() << endl;
    pR->SetLength(150.0);
    sql.UpdateBioCmp("Project Upgrade", cmp);
    runs = sql.GetBiomassPipeRuns("Project Upgrade");
    cmp = runs.at(0)->GetBioComponents();
    pR = dynamic_pointer_cast<CIRCUIT::PipeRunBiomass>(cmp);
    cout << pR->GetLength() << endl;
}



int main()
{
    //CreateDB();
    //CreatProject();
    //InsertTubes();
    //InsertTubes2();
    //InsertTubes3();
    //InsertTubes4();
    //InsertTubes5();
    //InsertPipeRuns();
    //LookAtDB();    
    //
    //ReadData();

    //GetPipeRun();
    //SetReferences();
    //WriteReferences();

    //TestRorPK();
    //AddTable();

    //GetCompleteProject();


    UpDatePipeInPipeRun();
    std::cout << "Finish!\n";
}


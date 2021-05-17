#include <DataInventory.h>
#include <VTKPipeLine.h>
#include <qdebug.h>


DataInventory &DataInventory::Get_Instance() {
    //create the singleton and return it
    static DataInventory Singleton;
    return Singleton;
}

void DataInventory::BoundSet_Push_Back(const QString &SourceName, double *Bound) {
    //insert key-value pair
    mBoundSet.insert(SourceName, Bound);
}

void DataInventory::ActorSet_Push_Back(const QString &SourceName, const vtkSmartPointer<vtkActor> &Actor) {
    //insert key-value pair
    mActorSet.insert(SourceName, Actor);
}

void DataInventory::PolyDataSet_Push_Back(const QString &SourceName, const vtkSmartPointer<vtkPolyData> &PolyData) {
    //insert key-value pair
    mPolyDataSet.insert(SourceName, PolyData);
}

void DataInventory::BoundSet_Pop_Back(const QString &SourceName) {
    //remove key-value pair
    mBoundSet.remove(SourceName);
}

void DataInventory::ActorSet_Pop_Back(const QString &SourceName) {
    //remove key-value pair
    mActorSet.remove(SourceName);
}

void DataInventory::PolyDataSet_Pop_Back(const QString &SourceName) {
    //remove key-value pair
    mPolyDataSet.remove(SourceName);
}


void DataInventory::Add_Data_To_Inventory(VTKPipeLine &PipeLine) {
    //execute polymorphism
    PipeLine.Store_Model_Data();
}

vtkSmartPointer<vtkActor> DataInventory::Get_Value_From_ActorSet(const QString &Key) const {
    //get value according to the key
    return mActorSet.value(Key);
}

vtkSmartPointer<vtkPolyData> DataInventory::Get_Value_From_PolyDataSet(const QString &Key) const {
    //get value according to the key
    return mPolyDataSet.value(Key);
}

double *DataInventory::Get_Value_From_BoundSet(const QString &Key) const {
    //get value according to the key
    return mBoundSet.value(Key);
}

bool DataInventory::operator==(const QString &Key) {
    //do the checking
    return mActorSet.contains(Key);
}


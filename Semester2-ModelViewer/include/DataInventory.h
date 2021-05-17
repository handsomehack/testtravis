#ifndef DATAINVENTORY_H
#define DATAINVENTORY_H
#include <qmap.h>
#include <vtkSmartPointer.h>
class VTKPipeLine;
class vtkActor;
class vtkPolyData;
class QString;

/*
 * CopyRight: Group 6
 * Author:JunZhe Fan
 */


///This class is used to store the Actor and information associated with it(e.g. bounding information, PolyData information)
///This class makes use of QT's Map container's key-value-pair feature to easily store, retrieve and delete data .
///This class is using Singleton design pattern because it makes sense that only one Inventory is needed
///and since the instance is declared as static and vtksmartpointer stored in the map container is using reference counting mechanism like std::share_ptr
///therefore it can make sure the information stored in the container stay valid until the users choose to delete it
class DataInventory {

public:

    ///This method is used to get the Singleton
    ///@return a reference to the Singleton
    static DataInventory &Get_Instance();

    ///This method is used to push data into the inventory
    ///@param PipeLine a reference to the derived class instance to trigger the polymorphism
    static void Add_Data_To_Inventory(VTKPipeLine& PipeLine);

    ///This method is used to push data into BoundSet
    ///@param SourceName name of the source
    ///@param a smart_ptr to the bounding information
    void BoundSet_Push_Back(const QString &SourceName, double *Bound);

    ///This method is used to push data into the ActorSet
    ///@param SourceName  name of the source
    ///@param Actor a smart_ptr to the actor
    void ActorSet_Push_Back(const QString &SourceName, const vtkSmartPointer<vtkActor> &Actor);

    ///This method is used to push data into the PolydataSet
    ///@param SourceName name of the source
    ///@param SourceName  a smart_ptr to the polydata
    void PolyDataSet_Push_Back(const QString &SourceName, const vtkSmartPointer<vtkPolyData> &PolyData);

    ///This method is used to remove data from the BoundSet
    ///@param SourceName name of the source you want to remove
    void BoundSet_Pop_Back(const QString& SourceName);

    ///This method is used to remove data from the ActorSet
    ///@param SourceName name of the source you want to remove
    void ActorSet_Pop_Back(const QString& SourceName);

    ///This method is used to remove data from the PolyDataSet
    ///@param SourceName name of the source you want to remove
    void PolyDataSet_Pop_Back(const QString& SourceName);

    ///This method is used to get data from the PolyDataset according to the key
    ///@param Key name of the source
    ///@return a pointer to the polydata with respect to the key
    vtkSmartPointer<vtkPolyData> Get_Value_From_PolyDataSet(const QString& Key) const;

    ///This method is used to get data from the Boundset according to the key
    ///@param Key name of the source
    ///@return a pointer to the bounds with respect to the key
    double* Get_Value_From_BoundSet(const QString& Key) const;

    ///This method is used to get data from the ActorSet according the key
    ///@param Key name of the source
    ///@return a pointer to the actor with respect to the key
    vtkSmartPointer<vtkActor> Get_Value_From_ActorSet(const QString& Key) const;

    ///This is an overloaded operator== to check if the Actor already existed  in the map
    ///@param Key name of the source you want to check
    ///@return if actor already existed, return true, otherwise return false
    bool operator==(const QString& Key);


    DataInventory(const DataInventory&)= delete;

    DataInventory& operator=(const DataInventory&)= delete;


private:

    DataInventory() = default;
    QMap<QString, double *> mBoundSet;
    QMap<QString, vtkSmartPointer<vtkActor>> mActorSet;
    QMap<QString, vtkSmartPointer<vtkPolyData>> mPolyDataSet;
};

#endif

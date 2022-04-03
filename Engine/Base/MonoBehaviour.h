#pragma once

namespace ArtemisEngine
{
    class MonoBehaviour
    {
    public:
        MonoBehaviour();
        ~MonoBehaviour();

        template <typename DerivedType>
        DerivedType* getDerived();


        void virtual Update();
        void virtual Render();

    private:

    };

    template <typename DerivedType>
    DerivedType* MonoBehaviour::getDerived()
    {
        return dynamic_cast<DerivedType*>(this);
    }
}



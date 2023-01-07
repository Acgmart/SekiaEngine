// Copyright (c) 2012-2022 Wojciech Figat. All rights reserved.

#include "TestScripting.h"
#include "Engine/Scripting/Scripting.h"
#include <ThirdParty/catch2/catch.hpp>

TestClassNative::TestClassNative(const SpawnParams& params)
    : ScriptingObject(params)
{
}

TEST_CASE("Scripting")
{
    SECTION("Test Class")
    {
        // Test native class
        ScriptingTypeHandle type = Scripting::FindScriptingType("FlaxEngine.TestClassNative");
        CHECK(type == TestClassNative::TypeInitializer);
        ScriptingObject* object = Scripting::NewObject(type);
        CHECK(object);
        CHECK(object->Is<TestClassNative>());
        TestClassNative* testClass = (TestClassNative*)object;
        CHECK(testClass->SimpleField == 1);
        CHECK(testClass->SimpleStruct.Object == nullptr);
        CHECK(testClass->SimpleStruct.Vector == Float3::One);
        Array<TestStruct> struct1 = { testClass->SimpleStruct };
        Array<TestStruct> struct2 = { testClass->SimpleStruct };
        Array<ScriptingObject*> objects;
        TestStructPOD pod;
        int32 methodResult = testClass->TestMethod(TEXT("123"), pod, struct1, struct2, objects);
        CHECK(methodResult == 3);
        CHECK(objects.Count() == 0);

        // Test managed class
        type = Scripting::FindScriptingType("FlaxEngine.TestClassManaged");
        CHECK(type);
        object = Scripting::NewObject(type);
        CHECK(object);
        CHECK(object->Is<TestClassNative>());
        testClass = (TestClassNative*)object;
        MObject* managed = testClass->GetOrCreateManagedInstance(); // Ensure to create C# object and run it's ctor
        CHECK(managed);
        CHECK(testClass->SimpleField == 2);
        CHECK(testClass->SimpleStruct.Object == testClass);
        CHECK(testClass->SimpleStruct.Vector == Float3::UnitX);
        struct1 = { testClass->SimpleStruct };
        struct2 = { testClass->SimpleStruct };
        objects.Clear();
        pod.Vector = Float3::One;
        methodResult = testClass->TestMethod(TEXT("123"), pod, struct1, struct2, objects);
        CHECK(methodResult == 6);
        CHECK(pod.Vector == Float3::Half);
        CHECK(struct2.Count() == 2);
        CHECK(struct2[0] == testClass->SimpleStruct);
        CHECK(struct2[1] == testClass->SimpleStruct);
        CHECK(objects.Count() == 3);
    }

    SECTION("Test Event")
    {
        ScriptingTypeHandle type = Scripting::FindScriptingType("FlaxEngine.TestClassManaged");
        CHECK(type);
        ScriptingObject* object = Scripting::NewObject(type);
        CHECK(object);
        MObject* managed = object->GetOrCreateManagedInstance(); // Ensure to create C# object and run it's ctor
        CHECK(managed);
        TestClassNative* testClass = (TestClassNative*)object;
        CHECK(testClass->SimpleField == 2);
        String str1 = TEXT("1");
        String str2 = TEXT("2");
        Array<TestStruct> arr1 = { testClass->SimpleStruct };
        Array<TestStruct> arr2 = { testClass->SimpleStruct };
        testClass->SimpleEvent(1, Float3::One, str1, str2, arr1, arr2);
        CHECK(testClass->SimpleField == 4);
        CHECK(str2 == TEXT("4"));
        CHECK(arr2.Count() == 2);
        CHECK(arr2[0].Vector == Float3::Half);
        CHECK(arr2[0].Object == nullptr);
        CHECK(arr2[1].Vector == testClass->SimpleStruct.Vector);
        CHECK(arr2[1].Object == testClass);
    }

    SECTION("Test Interface")
    {
        // Test native interface implementation
        ScriptingTypeHandle type = Scripting::FindScriptingType("FlaxEngine.TestClassNative");
        CHECK(type);
        ScriptingObject* object = Scripting::NewObject(type);
        CHECK(object);
        TestClassNative* testClass = (TestClassNative*)object;
        int32 methodResult = testClass->TestInterfaceMethod(TEXT("123"));
        CHECK(methodResult == 3);
        ITestInterface* interface = ScriptingObject::ToInterface<ITestInterface>(object);
        CHECK(interface);
        methodResult = interface->TestInterfaceMethod(TEXT("1234"));
        CHECK(methodResult == 4);
        ScriptingObject* interfaceObject = ScriptingObject::FromInterface<ITestInterface>(interface);
        CHECK(interfaceObject);
        CHECK(interfaceObject == object);

        // Test managed interface override
        type = Scripting::FindScriptingType("FlaxEngine.TestClassManaged");
        CHECK(type);
        object = Scripting::NewObject(type);
        CHECK(object);
        testClass = (TestClassNative*)object;
        methodResult = testClass->TestInterfaceMethod(TEXT("123"));
        CHECK(methodResult == 6);
        interface = ScriptingObject::ToInterface<ITestInterface>(object);
        CHECK(interface);
        methodResult = interface->TestInterfaceMethod(TEXT("1234"));
        CHECK(methodResult == 8);
        interfaceObject = ScriptingObject::FromInterface<ITestInterface>(interface);
        CHECK(interfaceObject);
        CHECK(interfaceObject == object);

        // Test managed interface implementation
        type = Scripting::FindScriptingType("FlaxEngine.TestInterfaceManaged");
        CHECK(type);
        object = Scripting::NewObject(type);
        CHECK(object);
        interface = ScriptingObject::ToInterface<ITestInterface>(object);
        CHECK(interface);
        methodResult = interface->TestInterfaceMethod(TEXT("1234"));
        CHECK(methodResult == 4);
        interfaceObject = ScriptingObject::FromInterface<ITestInterface>(interface);
        CHECK(interfaceObject);
        CHECK(interfaceObject == object);
    }
}

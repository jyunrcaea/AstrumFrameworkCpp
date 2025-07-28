# ✨ Astrum Framework

**C++23**과 **DirectX 11**을 기반으로 구축된 2D 게임 개발 프레임워크.

## 특징
### 1. 게임 객체의 기본 책임
다른 게임엔진과 달리, 트랜스폼(Position, Rotation, Scale) 및 렌더링을 컴포넌트로 분리하지 않고 통합하여 같이 관리합니다.  
이 둘을 제외한 다른 기능들은 모두 컴포넌트로 분리되어 필요에 따라 추가하여 관리합니다.
### 2. 트리 구조의 게임 객체 관리
`AstrumGroupObject`는 `AstrumObject`를 상속하는 모든 객체를 자식 객체로 지정할수 있으며, 이를 통해 모든 객체가 부모-자식 관계를 가지는 트리 관계도를 구성할수 있습니다.  
`AstrumGroupObject`의 트랜스폼이 변경될때마다, 자식까지 모두 영향을 받습니다.  
- Position 변경시 : 자식 객체도 좌표계에서 동일한 거리를 이동합니다.
- Rotation 변경시 : 자식 객체도 회전이 누적되며, 좌표계에서도 부모 좌표를 기준으로 상대적으로 회전됩니다.
- Scale 변경시 : 자식 객체도 같이 크기가 변경되며, 좌표계도 역시 팽창/수축하게 됩니다.
### 3. 자동으로 갱신되는 트랜스폼
`AstrumObject`의 Position/Rotation/Scale은 관찰자 패턴이 들어간 `AstrumObservedVector3` 자료형으로 관리되며,  
매번 값이 갱신될때마다 절대적인 좌표/회전/크기를 재계산하며, `AstrumGroupObject`의 경우 자식 객체까지 전파됩니다. 

---
## 핵심 객체 소개
### 1. 게임 객체
`IAstrumObject` : 게임 객체의 가장 기본이 되는 추상 인터페이스입니다.
- `AstrumObject` : 게임 객체의 기본을 갖춘, 비추상 클래스입니다.
  - `AstrumGroupObject` : 자식 객체(`IAstrumObject`)들을 가질수 있고 관리해주는, 객체를 묶어주는 역할의 게임 객체입니다.
  - `AstrumDrawableObject` : 그릴수 있는 게임 객체를 의미합니다. 월드/뷰/투영을 관리하며 상수 버퍼를 소유하고 있습니다.
    - `AstrumMaterialObject` : 머터리얼을 렌더링 하는 게임 객체입니다.
    - `AstrumPolygonsObject` : 다각형을 렌더링하는 게임 객체입니다.

이외에 `AstrumRectangleObject`, `AstrumCircleObject` 등이 있습니다.
### 2. 컴포넌트
`IAstrumComponent` : 모든 컴포넌트의 기반이 되는 인터페이스입니다. 
- `AstrumComponent` : 컴포넌트의 기본을 갖춘 비추상 클래스입니다.
  - `AstrumAABBColliderComponent` : AABB 충돌체 컴포넌트입니다.
  - `AstrumAnimatorComponent` : 좌표나 크기 등 부드럽게 변화를 주는 애니메이션 효과 컴포넌트입니다.
  - `AstrumFrameAnimationComponent`  : 여러장의 머터리얼을 순회해주는 스프라이트 애니메이션 컴포넌트입니다.

### 3. 렌더링 파이프라인
1.  `Draw()` 호출 : 게임 루프에서 각 `AstrumDrawableObject`의 `Draw()` 메소드가 호출됩니다.
2.  렌더링 큐에 등록: `Draw()` 함수 내에서 그릴 대상은 `AstrumRenderer::EnqueueRenderable()`를 통해 추가합니다.
3.  일괄 렌더링: `AstrumRenderer::Rendering()` 함수에서 큐를 비울때까지, 그릴수 있는 `IRenderable` 객체들의 `PreRender()`와 `Render()`를 순차적으로 호출합니다.
    - **`PreRender()`**: 월드/뷰/투영 행렬과 같은 변환 정보를 계산하고 상수 버퍼를 업데이트합니다.
    - **`Render()`**: 실제 그리기(Draw Call) 명령을 실행합니다.

### 4. 리소스
모두 RAII 패턴이 적용되며, 생성자를 호출하는 즉시 자원이 할당되고, 소멸자를 통해 안전하게 해제됩니다.  
(주의: 할당 이전에 AstrumFramework::Initialize()를 통해 초기화가 되어 있어야 합니다.)
- `AstrumImage` : 시스템 메모리에 올라오는 이미지
- `AstrumTexture` : GPU 메모리에 올라온 텍스쳐 (`AstrumImage`를 통해 가져옴)
- `AstrumMaterial` : `AstrumTexture`의 전체 또는 일부분을 참조해서, 몇몇 속성(투명도 등등)과 함께 최종적으로 그리는데 사용될수 있는 텍스쳐
- `AstrumSound` : FMOD를 사용한, 사운드의 기본 단위

---
## 싱글톤 소개
- `AstrumFramework`: WinAPI 창 생성, 메시지 루프 처리, 그리고 엔진의 핵심 모듈(Renderer, Input, Sound, Chrono)을 초기화하고 관리하는 메인 클래스입니다.
- `AstrumRenderer`: DirectX 11 디바이스 및 스왑 체인 설정, 렌더링 큐 관리, 기본 셰이더 파이프라인 제공 등 모든 그래픽 처리를 담당합니다.
- `AstrumCollisionSystem`: 모든 `AstrumColliderComponent`를 관리하며, 매 프레임 충돌을 검사하고 `OnCollisionEnter`, `OnCollisionExit` 이벤트를 발생시킵니다.
- `AstrumDirectInput`: DirectInput 8을 사용하여 키보드 및 마우스 입력을 처리합니다. `WasKeyPressed` (방금 눌림), `IsKeyPressed` (누르고 있음) 등 상태 기반의 직관적인 입력 확인을 지원합니다.
- `AstrumSoundManager`: FMOD 시스템을 초기화하고 마스터 채널 그룹을 관리합니다. `AstrumSound`와 `AstrumChannelGroup` 래퍼 클래스를 통해 사운드 리소스를 쉽게 제어할 수 있습니다.
- `AstrumTextureCache`: `DirectXTex` 라이브러리를 활용하여 DDS, PNG, JPG, TGA 등 다양한 형식의 이미지 파일을 로드하고, 한 번 로드된 텍스처는 캐싱하여 재사용함으로써 성능을 향상시킵니다.

---
## 시작하기
`Program.hpp`의 `Main()` 함수를 참고해보세요.
```cpp
#include "AstrumFramework.hpp"
#include "MyCustomObject.hpp" // 사용자 정의 객체

void PrepareShaders() {
    // 도형 렌더링을 위한 기본 셰이더 설정
    auto shapePipeline = AstrumShaderSetup::MakeShared()
    shapePipeline->VertexShader = AstrumVertexShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshVS");
    shapePipeline->PixelShader = AstrumPixelShader::MakeShared(L"./Shaders/ColorMesh.fx", "ColorMeshPS");
    shapePipeline->AddInputLayoutDescription("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0);
    shapePipeline->AddInputLayoutDescription("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0);
    AstrumRenderer::Instance().DefaultShapeShaderPipeline = shapePipeline;

    // 텍스처 렌더링을 위한 기본 셰이더 설정
    // (마찬가지로 shapePipeline처럼 설정해주면 됨.)
}

int main() {
    // 1. 프레임워크 초기화
    AstrumFramework::Initialize(L"My Astrum Game", 1280, 720);

    // 2. 기본 셰이더 준비
    PrepareShaders();

    // 3. 루트 객체에 씬(Scene) 또는 객체 할당
    auto myScene = std::make_shared<AstrumGroupObject>();
    auto myObject = std::make_shared<AstrumObject>();

    // 3-1. myScene를 부모로, myObject를 자식으로 추가
    myScene->AddObject(myObject);

    // 4. 루트 AstrumGroupObject 할당
    AstrumFramework::RootObject = myScene;

    // 5. 실행!
    AstrumFramework::Run();
}
```
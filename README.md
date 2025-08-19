# ✨ Astrum Framework

**C++23**과 **DirectX 11**을 기반으로 구축된 2D 게임 개발 프레임워크.

## 폴더 구조
- `Astum` 폴더 : 프레임워크를 구성하는 코드들입니다.
- `Game` 폴더 : 프레임워크를 사용하는 코드들입니다.

## 특징
### 1. 게임 객체의 기본 책임
 `AstrumObject`에서 트랜스폼(Position, Rotation, Scale)을 컴포넌트로 분리하지 않고 통합하여 같이 관리합니다.  
이외의 기능들은 모두 컴포넌트로 분리되어 필요에 따라 추가하여 관리합니다.
  
`IAstrumObject`는 기본적인 이벤트 함수로 다음 네가지를 가지고 있습니다.
(개발자가 임의로 호출할수도 있지만, 앞서 프레임워크의 기준으로 호출 기준을 설명합니다.)
- `Prepare()` : 게임 로직에서 실제로 사용되기 시작할때 호출되는 함수입니다. (`Update()`가 `Prepare()`보다 먼저 호출될수 없습니다.)
- `Update()` : 메 프레임마다 게임 로직에서 지속적으로 호출해주는 함수입니다. (델타 타임은 `AstrumChrono::GetDeltaTime()`으로 가져올수 있습니다.)
- `Release()` : 게임 로직에서 더이상 사용되지 않을때 호출되는 함수입니다. (`Release()`가 `Prepare()`보다 먼저 호출될수 없습니다.)
- `Draw()` : 렌더링 단계에 들어가기 직전에 호출되는 함수입니다. (매 프레임마다 `Update()`가 `Draw()`보다 먼저 호출됩니다.)
### 2. 트리 구조의 게임 객체 관리
해당 프레임워크에는 장면 기능을 제공하지 않습니다.  
대신 `AstrumObject`를 상속한 객체 여러개를 자식으로 가지며 앞서 말한 4개의 이벤트와 트렌스폼을 갱신해주면서,  
객체를 묶어주는 역할를 맡는 `AstrumGroupObject`이 장면의 역할을 대체합니다.  

`AstrumGroupObject`를 통해 부모-자식 관계를 갖는 트리 구조의 객체 관계를 가집니다.  
또한, 부모(`AstrumGroupObject`)의 트랜스폼이 변경될때마다, 자식까지 모두 영향을 받습니다.  
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
  - `AstrumMaterialObject` : 머터리얼을 렌더링 하는 게임 객체입니다.
  - `AstrumPolygonsObject` : 다각형을 렌더링하는 게임 객체입니다.
  - `AstrumRectangleObject` : 직사각형을 렌더링하는 게임 객체입니다.

### 2. 컴포넌트
`IAstrumComponent` : 모든 컴포넌트의 기반이 되는 인터페이스입니다. 
- `AstrumComponent` : 컴포넌트의 기본을 갖춘 비추상 클래스입니다.
  - `AstrumAABBColliderComponent` : AABB 충돌체 컴포넌트입니다.
  - `AstrumAnimatorComponent` : 좌표나 크기 등 부드럽게 변화를 주는 애니메이션 효과 컴포넌트입니다.
  - `AstrumFrameAnimationComponent`  : 여러장의 머터리얼을 순회해주는 스프라이트 애니메이션 컴포넌트입니다.
  - `AstrumRenderMaterialComponent` : 머터리얼을 렌더링 할수있는 컴포넌트입니다.
  - `AstrumRenderPolygonsComponent` : 다각형을 렌더링 할수있는 컴포넌트입니다.
  - `AstrumConstantBufferComponent` : 상수 버퍼를 관리하는 컴포넌트입니다. (주로 커스텀 셰이더를 사용했을때 필요해집니다)

### 3. 렌더링 파이프라인
1.  `IAstrumObject::Draw()` 호출 : `Update()`가 끝난 이후 `Draw()` 메소드가 호출됩니다.
2.  렌더링 큐에 등록: 그릴수 있는 객체들에 한해 오버라이딩 된 `Draw()` 함수에서 `AstrumRenderer::Instance().EnqueueRenderable(IAstrumRenderable)`를 통해 큐에 등록합니다.
3.  일괄 렌더링: `AstrumRenderer::Rendering()` 함수에서 큐를 비울때까지, `IAstrumRenderable::PreRender()`와 `IAstrumRenderable::Render()`를 순차적으로 호출합니다.
    - `PreRender()`: 월드/뷰/투영 행렬과 같은 변환 정보를 계산하고 상수 버퍼를 업데이트합니다. (일부 과정이 추가됬을수도 있지만, 기본적으로 이렇습니다.)
    - `Render()`: 실제 그리기(Draw Call) 명령을 실행합니다.

### 4. 리소스
모두 RAII 패턴이 적용되며, 생성자를 호출하는 즉시 자원이 할당되고, 소멸자를 통해 안전하게 해제됩니다.  
(주의: 할당 이전에 AstrumFramework::Initialize()를 통해 초기화가 되어 있어야 안정적으로 동작할수 있습니다.)
- `AstrumImage` : 시스템 메모리에 올라오는 이미지
- `AstrumTexture` : GPU 메모리에 올라온 텍스쳐 (`AstrumImage`를 통해 가져옴)
- `AstrumMaterial` : `AstrumTexture`의 전체 또는 일부분을 참조해서, 투명도와 함께 최종적으로 그리는데 사용될수 있는 텍스쳐
- `AstrumSound` : FMOD 라이브러리를 사용한, 사운드 그자체.

---
## 싱글톤 소개
### 기본적인 싱글톤
- `AstrumFramework`: 엔진을 초기화하고 실행하는 메인 클래스입니다.
- `AstrumWindow`: WinAPI 창을 생성하고 메시지 루프를 처리하는 클래스입니다.
- `AstrumRenderer`: DirectX 11 디바이스 및 스왑 체인 설정, 렌더링 큐 관리, 기본 셰이더 파이프라인 제공 등 모든 그래픽 처리를 담당합니다.
- `AstrumChrono`: 시간 관련 기능을 제공하는 클래스입니다. 프레임 제한, 델타 타임 등을 관리합니다.
- `AstrumCollisionSystem`: 모든 `AstrumColliderComponent`를 관리하며, 매 프레임 충돌을 검사하고 `OnCollisionEnter`, `OnCollisionExit` 이벤트를 발생시킵니다.
- `AstrumDirectInput`: DirectInput 8을 사용하여 키보드 및 마우스 입력을 처리합니다. `WasKeyPressed` (방금 눌림), `IsKeyPressed` (누르고 있음) 등 상태 기반의 직관적인 입력 확인을 지원합니다.

위 싱글톤들은 모두 의존성을 가집니다.

### 유용한 싱글톤
- `AstrumKeyBinder` : 한개 이상의 키 목록에 이름을 부여해서(`AddKeyBind(name, key)`), 해당 목록중에서 눌린 키가 하나라도 있는지 이름을 통해 조회합니다(`IsKeyPressed(name)`).
- `AstrumTextureCache` : 텍스쳐를 캐싱하여 중복 로딩을 방지합니다. `GetTexture(path)`를 통해 경로로 텍스쳐를 가져오고, 없으면 로드하여 캐싱합니다.

위 싱글톤들은 모두 편의를 위해 존재하며, 사용하지 않는 한, 기본적으로 의존성을 가지지 않습니다.

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
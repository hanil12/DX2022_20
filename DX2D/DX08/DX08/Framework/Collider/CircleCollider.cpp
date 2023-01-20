#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
: _radius(radius)
{
	CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	_transform->Update();
	_colorBuffer->Update();
}

void CircleCollider::Render()
{
    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    _vertexBuffer->IASet(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    float radiusSum = this->_radius * this->GetTransform()->GetWorldScale().x + other->_radius * other->GetTransform()->GetWorldScale().x;
    float distance = (other->_transform->GetWorldPos() - this->_transform->GetWorldPos()).Length();

    return distance < radiusSum;
}

void CircleCollider::CreateData()
{
	CreateVertices();

    _vs = make_shared<VertexShader>(L"Shader/Collider/ColliderVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/Collider/ColliderPixelShader.hlsl");

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Bagic), _vertices.size());

    _colorBuffer = make_shared<ColorBuffer>();
    _colorBuffer->_data.color = { 0,1,0,1 };
    _transform = make_shared<Transform>();
}

void CircleCollider::CreateVertices()
{
    float angle = PI / 18.0f;

    for (int i = 0; i < 37; i++)
    {
        Vertex_Bagic vertex;
        vertex.pos = XMFLOAT3(cos(angle * i) * _radius, sin(angle * i) * _radius, 0);
        _vertices.push_back(vertex);
    }
}
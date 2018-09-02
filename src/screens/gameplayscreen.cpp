#include "gameplayscreen.h"

#include "../platformerjam.h"


GameplayScreen::GameplayScreen(PlatformerJam *game)
    : m_collisionTilemap(10, 10, 32, 32, {
                         0,0,0,1,1,1,1,1,1,1,
                         0,0,0,0,0,1,0,0,0,0,
                         0,0,0,0,0,1,0,0,0,0,
                         0,0,0,0,0,1,0,0,0,0,
                         0,0,0,0,0,1,0,0,1,0,
                         0,0,0,0,0,0,0,0,1,0,
                         0,0,0,0,0,0,0,0,1,0,
                         0,0,0,1,0,0,0,0,1,0,
                         0,0,0,1,0,0,0,0,1,0,
                         1,1,1,1,1,1,1,1,1,1,
                         }),
      m_playerRect(0, 0, 48, 48)
{
    m_game = game;
}

void GameplayScreen::show()
{

}

void GameplayScreen::hide()
{

}

void GameplayScreen::render()
{
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 0, 0, 1, 1, 0);
    al_use_transform(&tr);

    aether::graphics::clear(1, 0, 0);

    const auto& m = m_collisionTilemap.map();
    float tw = m_collisionTilemap.tileWidth();
    float th = m_collisionTilemap.tileHeight();

    for( size_t i = 0; i < m.rows(); i++ )
    {
        for( size_t j = 0; j < m.cols(); j++ )
        {
            if( m_collisionTilemap.isSolid(j, i) )
            {
                aether::graphics::draw_filled_rectangle(j * tw, i * th, (j+1)*tw, (i+1)*th, aether::graphics::Color(255, 255, 0));
            }
            else
            {
                aether::graphics::draw_filled_rectangle(j * tw, i * th, (j+1)*tw, (i+1)*th, aether::graphics::Color(255, 0, 255));
            }
        }
    }

    aether::graphics::draw_filled_rectangle(m_playerRect, aether::graphics::Color(0, 255, 255));
}


void GameplayScreen::update(uint64_t delta)
{
    int prx, pry, spd, dx, dy;
    prx = m_playerRect.x();
    pry = m_playerRect.y();
    spd = 3;
    dx = dy = 0;

    if( aether::core::is_key_down(aether::core::KeyCode::Left) )
    {
        dx = -spd;
    }

    if( aether::core::is_key_down(aether::core::KeyCode::Right) )
    {
        dx = spd;
    }

    if( aether::core::is_key_down(aether::core::KeyCode::Up) )
    {
        dy = -spd;
    }

    if( aether::core::is_key_down(aether::core::KeyCode::Down) )
    {
        dy = spd;
    }

    if( dx != 0 || dy != 0 )
    {
        m_collisionTilemap.realmove(m_playerRect, prx + dx, pry + dy);
    }

}
